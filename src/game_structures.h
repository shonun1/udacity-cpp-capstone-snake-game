#ifndef GAME_STRUCTURES_H
#define GAME_STRUCTURES_H

#include <vector>

#include "SDL.h"

// TODO: is there a better way to resolve circular dependency?
enum class GameState { Running, Paused, Terminated };

class Color {
 public:
  // Constructors
  Color() {};
  Color(std::string name_, int red, int green, int blue)
      : name(name_), r(red), g(green), b(blue), a(0xFF) {};
  Color(std::string name_, int red, int green, int blue, int alpha)
      : name(name_), r(red), g(green), b(blue), a(alpha) {};

  std::string Name() const { return name; }
  int R() const { return r; }
  int G() const { return g; }
  int B() const { return b; }
  int A() const { return a; }

  static const std::vector<Color> COLOR_OPTIONS;

 private:
  std::string name;
  int r, g, b, a;
};

struct Food {
  SDL_Point point;
  Color color;
};

#endif