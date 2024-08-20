#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "SDL.h"
#include "game_structures.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           GameSettings *game_settings);
  ~Renderer();

  void Render(Snake const snake, Food const &food);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  GameSettings *settings;

  const std::size_t screen_width;
  const std::size_t screen_height;
};

#endif