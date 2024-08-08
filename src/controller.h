#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "game_state.h"
#include "snake.h"

class Controller {
 public:
  void HandleInput(GameState &state, Snake &snake) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif