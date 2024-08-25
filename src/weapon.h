#ifndef WEAPON_H
#define WEAPON_H

#include <list>

#include "game_structures.h"
#include "missile.h"

class Weapon {
 public:
  enum class Type { FoodCatcher, FreezingGun, DisorientingGun };

  int GetAmmo() const { return ammo; }
  int GetConsecutiveShots() const { return consecutive_shots; }
  Weapon::Type GetType() const { return type; }
  std::list<Missile> GetMissiles() const { return missiles; }

  void GenerateWeapon();
  void AddAmmo(int amount);
  void Shoot(float x, float y, float speed, Direction dir);
  void UpdateMissiles(const GridSize &gridSize);

 private:
  Type type;
  std::list<Missile> missiles{};
  int ammo{0};
  int consecutive_shots{0};
};

#endif