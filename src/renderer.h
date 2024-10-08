#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "SDL.h"
#include "SDL_ttf.h"
#include "game_structures.h"
#include "snake.h"

class Renderer {
 public:
  // Constructor / Destructor
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           std::shared_ptr<GameSettings> game_settings);
  ~Renderer();

  // Class methods
  void Render(Snake const &snake, Food const &food, GameState state,
              const Menu &menu);
  void UpdateWindowTitle(int score, int fps, Snake &snake);

 private:
  // Static private members / methods
  static void InitializeFont();
  static const char *FONT_PATH;
  static const int FONT_SIZE;
  static TTF_Font *FONT;

  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  std::shared_ptr<GameSettings> settings;

  const std::size_t screen_width;
  const std::size_t screen_height;
};

#endif