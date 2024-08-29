#ifndef GAME_STRUCTURES_H
#define GAME_STRUCTURES_H

#include <functional>
#include <vector>

#include "SDL.h"

// TODO: is there a better way to resolve circular dependency?
enum class GameState { Running, Paused, Terminated };
enum class Direction { kUp, kDown, kLeft, kRight };

class Color {
 public:
  // Constructors
  Color() : name("white"), r(0xFF), g(0xFF), b(0xFF), a(0xFF) {};
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

  GridSize::Options GetSize() const { return size; }
  int GetWidth() const { return width; }
  int GetHeight() const { return height; }

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
  void SelectNextGridSize();

 private:
  std::string username{"user"};
  GridSize gridSize;

  void SaveToFile();
};

class Menu {
 public:
  std::vector<std::string> GetItems() const { return items; }
  int GetSelectedItem() const { return selectedItem; }

  void AddMenuItem(const std::string& item, std::function<void()> action) {
    items.push_back(item);
    actions.push_back(action);
  }

  void ExecuteSelectedItemAction() const {
    if (selectedItem >= 0 && selectedItem < actions.size()) {
      actions[selectedItem]();
    }
  }

  void SelectPreviousItem() {
    selectedItem = (selectedItem - 1) % items.size();
  }
  void SelectNextItem() { selectedItem = (selectedItem + 1) % items.size(); }

 private:
  std::vector<std::string> items;
  std::vector<std::function<void()>> actions;
  int selectedItem{0};
};

#endif