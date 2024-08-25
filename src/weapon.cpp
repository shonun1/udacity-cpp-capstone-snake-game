#include "weapon.h"

#include <iostream>

void Weapon::GenerateWeapon() {
  if (type != Weapon::Type::FoodCatcher) return;

  type = static_cast<Weapon::Type>(rand() % 3);
}

void Weapon::AddAmmo(int amount) { ammo += amount; }

void Weapon::Shoot(float x, float y, float speed, Direction dir) {
  if (ammo <= 0) return;
  ammo--;
  consecutive_shots++;
  if (consecutive_shots / 10 > 0) {
    consecutive_shots = 0;
    type = Weapon::Type::FoodCatcher;
  }
  // TODO: calculate the very next spot ahead of head based on dir
  missiles.emplace_back(x, y, speed, dir);
}

void Weapon::UpdateMissiles(const GridSize &gridSize) {
  for (auto it = missiles.begin(); it != missiles.end();) {
    it->UpdatePosition();
    if (it->HasHitWall(gridSize)) {
      it = missiles.erase(it);
    } else {
      ++it;
    }
  }
}
