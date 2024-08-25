#include "renderer.h"

#include <iostream>
#include <string>

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
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const &snake, Food const &food) {
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

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps, Snake &snake) {
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
