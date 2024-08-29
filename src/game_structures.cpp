#include "game_structures.h"

#include <fstream>
#include <unordered_map>

// Static variables value assignment
const std::string Score::SCORES_FILE = "../game_config/scores.txt";
const std::string GameSettings::SETTINGS_FILE = "../game_config/settings.txt";

const std::vector<Color> Color::COLOR_OPTIONS{
    Color("red", 0xFF, 0x00, 0x00),  Color("green", 0x00, 0xFF, 0x00),
    Color("blue", 0x00, 0x00, 0xFF), Color("yellow", 0xFF, 0xFF, 0x00),
    Color("cyan", 0x00, 0xFF, 0xFF), Color("magenta", 0xFF, 0x00, 0xFF),
    Color("white", 0xFF, 0xFF, 0xFF)};

const std::vector<GridSize> GridSize::GRID_SIZES{
    GridSize(GridSize::Options::Small), GridSize(GridSize::Options::Medium),
    GridSize(GridSize::Options::Large)};

GameSettings::GameSettings() {
  std::ifstream settings_file;
  std::string key, value;
  settings_file.open(GameSettings::SETTINGS_FILE);

  // Read the settings file into a local map
  std::unordered_map<std::string, std::string> settings_map;
  while (settings_file >> key >> value) {
    settings_map[key] = value;
  }
  settings_file.close();

  // Map the values onto GameSettings class members
  if (settings_map.count("username") > 0) username = settings_map["username"];
  if (settings_map.count("gridSize") > 0) {
    int gridSizeInt = std::stoi(settings_map["gridSize"]);
    if (gridSizeInt > 0 && gridSizeInt <= 2) {
      GridSize::Options gridSizeOption =
          static_cast<GridSize::Options>(gridSizeInt);
      gridSize = GridSize(gridSizeOption);
    }
  }

  SaveToFile();
}

void GameSettings::SetUsername(std::string newUsername) {
  username = newUsername;
  SaveToFile();
}

void GameSettings::SetGridSize(GridSize newSize) {
  gridSize = newSize;
  SaveToFile();
}

void GameSettings::SelectNextGridSize() {
  int curr_size = static_cast<int>(gridSize.GetSize());
  gridSize =
      GridSize::GRID_SIZES[(curr_size + 1) % GridSize::GRID_SIZES.size()];
  SaveToFile();
}

void GameSettings::SaveToFile() {
  std::ofstream settings_file;
  settings_file.open(GameSettings::SETTINGS_FILE, std::ios::trunc);
  settings_file << "username" << " " << username << std::endl;
  settings_file << "gridSize" << " " << static_cast<int>(gridSize.GetSize())
                << std::endl;

  settings_file.close();
}

GridSize::GridSize() {
  size = GridSize::Options::Small;
  width = 32;
  height = 32;
}

GridSize::GridSize(Options option) : size(option) {
  int side_length;
  switch (option) {
    case GridSize::Options::Small:
      side_length = 32;
      break;

    case GridSize::Options::Medium:
      side_length = 48;
      break;

    case GridSize::Options::Large:
      side_length = 64;
      break;
  }
  width = side_length;
  height = side_length;
}
