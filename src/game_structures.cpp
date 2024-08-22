#include "game_structures.h"

#include <fstream>
#include <unordered_map>

const std::string Score::SCORES_FILE = "../game_config/scores.txt";
const std::string GameSettings::SETTINGS_FILE = "../game_config/settings.txt";

const std::vector<Color> Color::COLOR_OPTIONS{
    Color("red", 0xFF, 0x00, 0x00),  Color("green", 0x00, 0xFF, 0x00),
    Color("blue", 0x00, 0x00, 0xFF), Color("yellow", 0xFF, 0xFF, 0x00),
    Color("cyan", 0x00, 0xFF, 0xFF), Color("magenta", 0xFF, 0x00, 0xFF),
    Color("white", 0xFF, 0xFF, 0xFF)};

const std::vector<GridSize> GridSize::GRID_SIZES{
    GridSize(32, 32), GridSize(48, 48), GridSize(64, 64)};

GameSettings::GameSettings() {
  std::ifstream settings_file;
  std::string key, value;
  settings_file.open(GameSettings::SETTINGS_FILE);

  std::unordered_map<std::string, std::string> settings_map;
  while (settings_file >> key >> value) {
    settings_map[key] = value;
  }
  settings_file.close();

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

void GameSettings::setUsername(std::string newUsername) {
  username = newUsername;
  SaveToFile();
}

void GameSettings::setGridSize(GridSize newSize) {
  gridSize = newSize;
  SaveToFile();
}

void GameSettings::SaveToFile() {
  std::ofstream settings_file;
  settings_file.open(GameSettings::SETTINGS_FILE, std::ios::trunc);
  settings_file << "username" << " " << username << std::endl;
  settings_file << "gridSize" << " " << static_cast<int>(gridSize.getSize())
                << std::endl;

  settings_file.close();
}

GridSize::GridSize() {
  size = GridSize::Options::Small;
  const GridSize& sizeData = GRID_SIZES[static_cast<int>(size)];
  width = sizeData.width;
  height = sizeData.height;
}

GridSize::GridSize(Options option) {
  size = option;
  const GridSize& sizeData = GRID_SIZES[static_cast<int>(option)];
  width = sizeData.width;
  height = sizeData.height;
}
