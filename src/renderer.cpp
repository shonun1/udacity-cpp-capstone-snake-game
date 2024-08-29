#include "renderer.h"

#include <iostream>
#include <string>

// Static variables value assignment
const SDL_Color SDL_WHITE{0xFF, 0xFF, 0xFF, 0xFF};
const SDL_Color SDL_RED{0xFF, 0x00, 0x00, 0xFF};
const char *Renderer::FONT_PATH{"../game_config/Jersey10-Regular.ttf"};
const int Renderer::FONT_SIZE{30};
TTF_Font *Renderer::FONT = nullptr;

void Renderer::InitializeFont() {
  Renderer::FONT = TTF_OpenFont(Renderer::FONT_PATH, Renderer::FONT_SIZE);
  if (!Renderer::FONT) {
    std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
  }
}

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height, GameSettings *game_settings)
    : screen_width(screen_width),
      screen_height(screen_height),
      settings(game_settings) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Initialize TTF
  if (TTF_Init() < 0) {
    std::cerr << "TTF could not initialize.\n";
    std::cerr << "TTF_Error: " << TTF_GetError() << "\n";
  }

  Renderer::InitializeFont();
}

Renderer::~Renderer() {
  TTF_Quit();
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const &snake, Food const &food, GameState state,
                      const Menu &menu) {
  SDL_Rect block;
  GridSize gridSize = settings->GetGridSize();
  block.w = screen_width / gridSize.GetWidth();
  block.h = screen_height / gridSize.GetHeight();

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, food.color.R(), food.color.G(),
                         food.color.B(), food.color.A());
  block.x = food.point.x * block.w;
  block.y = food.point.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // TODO: The missile gun must be saved in missile data to render correctly
  // Render missiles
  Color missile_color;
  switch (snake.GetWeapon()->GetType()) {
    case Weapon::Type::FoodCatcher:
      missile_color = Color();
      break;

    case Weapon::Type::FreezingGun:
      missile_color = Color("ice", 0x87, 0xCE, 0xEB);
      break;

    case Weapon::Type::DisorientingGun:
      missile_color = Color("magenta", 0xFF, 0x00, 0xFF);
      break;
  }
  for (const Missile &missile : snake.GetWeapon()->GetMissiles()) {
    block.x = static_cast<int>(missile.x_pos) * block.w;
    block.y = static_cast<int>(missile.y_pos) * block.h;
    SDL_SetRenderDrawColor(sdl_renderer, missile_color.R(), missile_color.G(),
                           missile_color.B(), missile_color.A());
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render menu
  if (state == GameState::Paused) {
    std::vector<std::string> menu_items = menu.GetItems();
    std::vector<SDL_Texture *> menu_textures;
    std::vector<SDL_Rect> menu_rects;
    int highlighted_item = menu.GetSelectedItem();

    for (size_t i = 0; i < menu_items.size(); ++i) {
      bool is_selected = i == highlighted_item;
      std::string selected_prefix = is_selected ? "> " : "";
      std::string item_text = selected_prefix + menu_items[i];
      SDL_Surface *text_surface = TTF_RenderText_Solid(
          FONT, item_text.c_str(), is_selected ? SDL_RED : SDL_WHITE);
      if (!text_surface) {
        std::cerr << "Failed to render text surface: " << TTF_GetError()
                  << std::endl;
        continue;
      }

      SDL_Texture *texture =
          SDL_CreateTextureFromSurface(sdl_renderer, text_surface);
      SDL_FreeSurface(text_surface);
      if (!texture) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError()
                  << std::endl;
        continue;
      }

      SDL_Rect rect;
      rect.w = 200;
      rect.h = 50;
      rect.x = screen_width / 2 - rect.w / 2;
      rect.y = 200 + i * 50;

      menu_textures.push_back(texture);
      menu_rects.push_back(rect);
    }

    for (size_t i = 0; i < menu_textures.size(); ++i) {
      if (SDL_RenderCopy(sdl_renderer, menu_textures[i], NULL,
                         &menu_rects[i]) != 0) {
        std::cerr << "Failed to render texture: " << SDL_GetError()
                  << std::endl;
      }
    }
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps, Snake &snake) {
  // Collect weapon information
  std::string weapon;
  switch (snake.GetWeapon()->GetType()) {
    case Weapon::Type::FoodCatcher:
      weapon = "Food Catcher";
      break;

    case Weapon::Type::FreezingGun:
      weapon = "Freezing Gun";
      break;

    case Weapon::Type::DisorientingGun:
      weapon = "Disorienting Gun";
      break;
  }
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " +
                    std::to_string(fps) + " Snake Weapon: " + weapon +
                    " Ammo: " + std::to_string(snake.GetWeapon()->GetAmmo())};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
