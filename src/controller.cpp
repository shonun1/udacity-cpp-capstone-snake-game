#include "controller.h"

#include <iostream>

#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Direction input,
                                 Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(GameState &state, Snake &snake, Menu &menu) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      state = GameState::Terminated;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          if (state == GameState::Running) {
            ChangeDirection(snake, Direction::kUp, Direction::kDown);
          } else {
            menu.SelectPreviousItem();
          }
          break;

        case SDLK_DOWN:
          if (state == GameState::Running) {
            ChangeDirection(snake, Direction::kDown, Direction::kUp);
          } else {
            menu.SelectNextItem();
          }
          break;

        case SDLK_LEFT:
          if (state == GameState::Running)
            ChangeDirection(snake, Direction::kLeft, Direction::kRight);
          break;

        case SDLK_RIGHT:
          if (state == GameState::Running)
            ChangeDirection(snake, Direction::kRight, Direction::kLeft);
          break;

        case SDLK_ESCAPE:
          if (state == GameState::Paused) {
            state = GameState::Running;
          } else {
            // TODO: consider game restarting might be implemented in the future
            state = GameState::Paused;
          }
          break;

        case SDLK_SPACE:
          if (state == GameState::Running)
            snake.GetWeapon()->Shoot(snake.head_x, snake.head_y,
                                     snake.speed + 0.2f, snake.direction);
          break;

        case SDLK_RETURN:
          if (state == GameState::Paused) menu.ExecuteSelectedItemAction();
          break;
      }
    }
  }
}