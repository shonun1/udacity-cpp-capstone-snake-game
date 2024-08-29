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
  Game(GameSettings *game_settings);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

  void ContinueGame() { state = GameState::Running; }
  void QuitGame() { state = GameState::Terminated; }
  void SelectNextGridSize();

 private:
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

  void PlaceFood();
  void Update();
  void WriteScoreToFile();
};

#endif