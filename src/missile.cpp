#include "missile.h"

#include "snake.h"

void Missile::UpdatePosition() {
  switch (this->direction) {
    case Direction::kUp:
      this->y_pos -= this->speed;
      break;

    case Direction::kDown:
      this->y_pos += this->speed;
      break;

    case Direction::kLeft:
      this->x_pos -= this->speed;
      break;

    case Direction::kRight:
      this->x_pos += this->speed;
      break;
  }
}

bool Missile::HasHitWall(const GridSize &gridSize) {
  return x_pos >= gridSize.GetHeight() || y_pos >= gridSize.GetWidth() ||
         x_pos <= 0 || y_pos <= 0;
}
