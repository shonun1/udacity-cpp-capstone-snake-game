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

struct Score {
  static const std::string SCORES_FILE;

  Score(std::string username_, int score_)
      : username(username_), score(score_) {};

  std::string username;
  int score;
};

class GridSize {
 public:
  enum class Options { Small, Medium, Large };
  GridSize();
  GridSize(Options option);
  GridSize(int width_, int height_) : width(width_), height(height_) {};

  GridSize::Options getSize() { return size; }
  int getWidth() { return width; }
  int getHeight() { return height; }

  static const std::vector<GridSize> GRID_SIZES;

 private:
  int width, height;
  GridSize::Options size;
};

class GameSettings {
 public:
  static const std::string SETTINGS_FILE;

  GameSettings();

  std::string GetUsername() const { return username; };
  GridSize GetGridSize() const { return gridSize; };
  void SetUsername(std::string newUsername);
  void SetGridSize(GridSize newSize);

  static const std::vector<GridSize> GRID_SIZE_OPTIONS;

 private:
  std::string username{"user"};
  GridSize gridSize;

  void SaveToFile();
};

#endif