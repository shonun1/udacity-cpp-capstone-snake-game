#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "SDL.h"
#include "SDL_ttf.h"
#include "game_structures.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           GameSettings *game_settings);
  ~Renderer();

  void Render(Snake const &snake, Food const &food, GameState state,
              const Menu &menu);
  void UpdateWindowTitle(int score, int fps, Snake &snake);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  GameSettings *settings;

  const std::size_t screen_width;
  const std::size_t screen_height;

  static void Initialize();
  static const char *FONT_PATH;
  static const int FONT_SIZE;
  static TTF_Font *FONT;
};

#endif