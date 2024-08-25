#ifndef MISSILE_H
#define MISSILE_H

#include "game_structures.h"

struct Missile {
  Missile(float x, float y, float mis_speed, Direction dir)
      : x_pos(x), y_pos(y), speed(mis_speed), direction(dir) {};

  void UpdatePosition();
  bool HasHitWall(const GridSize &gridSize);

  float x_pos;
  float y_pos;
  float speed;
  Direction direction;
};

#endif