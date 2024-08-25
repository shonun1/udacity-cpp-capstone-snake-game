#ifndef SNAKE_H
#define SNAKE_H

#include <list>
#include <vector>

#include "SDL.h"
#include "game_structures.h"
#include "weapon.h"

class Snake {
 public:
  Snake(GameSettings *game_settings) {
    settings = game_settings;
    GridSize gridSize = settings->GetGridSize();
    head_x = gridSize.GetWidth() / 2;
    head_y = gridSize.GetHeight() / 2;
  }

  void Update();
  void GrowBody();
  bool SnakeCell(int x, int y);
  Weapon *GetWeapon() const { return weapon.get(); }

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  bool growing{false};
  std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>();
  GameSettings *settings;
};

#endif