#include "controller.h"

#include <iostream>

#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake &snake, Direction input,
                                 Direction opposite) const {
  if (snake.direction != opposite || snake.size == 1) snake.direction = input;
  return;
}

void Controller::HandleInput(GameState &state, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      state = GameState::Terminated;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake, Direction::kUp, Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(snake, Direction::kDown, Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake, Direction::kLeft, Direction::kRight);
          break;

        case SDLK_RIGHT:
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
          snake.GetWeapon()->Shoot(snake.head_x, snake.head_y,
                                   snake.speed + 0.2f, snake.direction);
          break;
      }
    }
  }
}