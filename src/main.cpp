#include <future>
#include <iostream>
#include <memory>

#include "controller.h"
#include "game.h"
#include "game_structures.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};

  // Instantiate a shared settings class
  std::shared_ptr<GameSettings> settings = std::make_shared<GameSettings>();
  Renderer renderer(kScreenWidth, kScreenHeight, settings);
  Controller controller;
  Game game(settings);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}