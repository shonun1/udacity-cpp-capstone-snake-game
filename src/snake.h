#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include "SDL.h"
#include "game_structures.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };
  enum class Weapon { Gun, FreezingGun, DisorientingGun };

  Snake(GameSettings *game_settings) {
    settings = game_settings;
    GridSize gridSize = settings->GetGridSize();
    head_x = gridSize.GetWidth() / 2;
    head_y = gridSize.GetHeight() / 2;
  }

  int GetAmmo() const { return ammo; }
  Weapon GetWeapon() const { return weapon; }

  void Update();
  void GrowBody();
  bool SnakeCell(int x, int y);
  void GenerateWeapon();
  void AddAmmo(int amount);
  void Shoot();

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
  Weapon weapon;
  int ammo{0};
  GameSettings *settings;
};

#endif