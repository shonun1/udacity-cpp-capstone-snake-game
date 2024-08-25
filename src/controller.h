#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "game_structures.h"
#include "snake.h"

class Controller {
 public:
  void HandleInput(GameState &state, Snake &snake) const;

 private:
  void ChangeDirection(Snake &snake, Direction input, Direction opposite) const;
};

#endif