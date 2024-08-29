#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>

#include "SDL.h"
#include "controller.h"
#include "game_structures.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  // Constructor
  Game(GameSettings *game_settings);

  // Getters
  int GetScore() const;
  int GetSize() const;

  // Class methods
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  void ContinueGame() { state = GameState::Running; }
  void QuitGame() { state = GameState::Terminated; }
  void SelectNextGridSize();

 private:
  // Private class methods
  void PlaceFood();
  void Update();
  void WriteScoreToFile();

  GameState state;
  std::unique_ptr<Snake> snake;
  Food food;
  std::vector<Score> past_scores;
  GameSettings *settings;
  Menu menu;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::uniform_int_distribution<int> random_color;

  int score{0};
};

#endif