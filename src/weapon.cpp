#include "weapon.h"

#include <iostream>

void Weapon::GenerateWeapon() {
  // Generate a new weapon only if the default one is used
  if (type != Weapon::Type::FoodCatcher) return;

  // A simple pseudo-random weapon generation
  type = static_cast<Weapon::Type>(rand() % 3);
}

void Weapon::AddAmmo(int amount) { ammo += amount; }

void Weapon::Shoot(float x, float y, float speed, Direction dir) {
  if (ammo <= 0) return;
  ammo--;
  // Calculate the consecutive shots with the current weapon in order to
  // properly change back to basic weapon
  consecutive_shots++;
  if (consecutive_shots / 10 > 0) {
    consecutive_shots = 0;
    type = Weapon::Type::FoodCatcher;
  }
  // Store the Missile instances in the class member
  missiles.emplace_back(x, y, speed, dir);
}

void Weapon::UpdateMissiles(const GridSize &gridSize) {
  // Iterate over the list of Missile(s) and update each position. Once a
  // missile reaches the end of the grid, it is erased from the list.
  for (auto it = missiles.begin(); it != missiles.end();) {
    it->UpdatePosition();
    if (it->HasHitWall(gridSize)) {
      it = missiles.erase(it);
    } else {
      ++it;
    }
  }
}
