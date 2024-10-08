#include "game.h"

#include <chrono>
#include <fstream>
#include <iostream>

#include "SDL.h"

Game::Game(std::shared_ptr<GameSettings> game_settings)
    : engine(dev()), settings(game_settings) {
  GridSize gridSize = game_settings->GetGridSize();
  // Game class owns the Snake class instance
  snake = std::make_unique<Snake>(game_settings);

  random_w = std::uniform_int_distribution<int>(
      0, static_cast<int>(gridSize.GetWidth() - 1));
  random_h = std::uniform_int_distribution<int>(
      0, static_cast<int>(gridSize.GetHeight() - 1));

  // Read the scores from file into the class member
  std::string username;
  int past_score;
  std::ifstream scores_file;
  scores_file.open(Score::SCORES_FILE);

  while (scores_file >> username >> past_score) {
    past_scores.emplace_back(username, past_score);
  }
  scores_file.close();

  PlaceFood();

  // Add menu items and their actions
  menu.AddMenuItem("Continue", [this]() { ContinueGame(); });
  menu.AddMenuItem("Grid Size", [this]() { SelectNextGridSize(); });
  menu.AddMenuItem("Quit", [this]() { QuitGame(); });
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  int title_updates_count = 0;
  int last_fps = 0;
  state = GameState::Running;

  while (state != GameState::Terminated) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(state, *snake, menu);
    Update();
    renderer.Render(*snake, food, state, menu);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 100) {
      title_updates_count++;
      if (title_updates_count % 10 == 0) {
        last_fps = frame_count;
        frame_count = 0;
      }
      renderer.UpdateWindowTitle(score, last_fps, *snake);
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake->SnakeCell(x, y)) {
      food.point.x = x;
      food.point.y = y;
      int colorIdx = random_color(engine) % Color::COLOR_OPTIONS.size();
      food.color = Color::COLOR_OPTIONS[colorIdx];
      std::lock_guard<std::mutex> lock(mutex);
      food.is_toxic = colorIdx % 3 == 0 && allow_toxic_food;

      return;
    }
  }
}

void Game::Update() {
  if (state == GameState::Paused) return;
  if (!snake->alive) {
    WriteScoreToFile();
    state = GameState::Terminated;
    return;
  }

  snake->Update();

  int new_x = static_cast<int>(snake->head_x);
  int new_y = static_cast<int>(snake->head_y);
  bool any_missile_hit_food{false};
  std::list<Missile> missiles = snake->GetWeapon()->GetMissiles();
  for (Missile missile : missiles) {
    int missile_x = static_cast<int>(missile.x_pos);
    int missile_y = static_cast<int>(missile.y_pos);
    if (missile_x == food.point.x && missile_y == food.point.y)
      any_missile_hit_food = true;
    if (any_missile_hit_food) break;
  }

  // Check if there's food over here
  if (any_missile_hit_food ||
      (food.point.x == new_x && food.point.y == new_y)) {
    score++;

    if (food.is_toxic) {
      // Temporarily slow down the snake if the food was toxic
      last_slowdown = snake->speed / 2.f;
      std::unique_lock<std::mutex> lock(mutex);
      snake->speed -= last_slowdown;
      allow_toxic_food = false;
      lock.unlock();
      slowdown_thread = std::thread(&Game::SlowdownTimer, this);
      slowdown_thread.detach();
    } else {
      // Grow snake and increase speed
      snake->GrowBody();
      std::lock_guard<std::mutex> lock(mutex);
      snake->speed += 0.02;
    }

    PlaceFood();
    snake->GetWeapon()->AddAmmo(score);
    snake->GetWeapon()->GenerateWeapon();
  }
}

void Game::WriteScoreToFile() {
  std::ofstream scores_file;

  scores_file.open(Score::SCORES_FILE, std::ios_base::app);
  scores_file << settings->GetUsername() << " " << score << std::endl;
  scores_file.close();
}

void Game::SlowdownTimer() {
  const int slowdownSeconds = 5;
  auto elapsedMs = std::chrono::milliseconds(0);
  auto lastLoopTime = std::chrono::high_resolution_clock::now();
  while (std::chrono::duration_cast<std::chrono::seconds>(elapsedMs).count() <
         slowdownSeconds) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    auto msSinceLastLoop =
        std::chrono::duration_cast<std::chrono::milliseconds>(currentTime -
                                                              lastLoopTime);
    lastLoopTime = currentTime;
    if (state == GameState::Running) elapsedMs += msSinceLastLoop;
    std::this_thread::sleep_for(std::chrono::milliseconds(900));
  }

  std::lock_guard<std::mutex> lock(mutex);
  allow_toxic_food = true;
  snake->speed += last_slowdown;
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake->size; }

void Game::SelectNextGridSize() {
  settings->SelectNextGridSize();

  // Update the class members to correctly reflect on the grid size change
  GridSize gridSize = settings->GetGridSize();
  random_w = std::uniform_int_distribution<int>(
      0, static_cast<int>(gridSize.GetWidth() - 1));
  random_h = std::uniform_int_distribution<int>(
      0, static_cast<int>(gridSize.GetHeight() - 1));

  // Place new food if the food turns out to be out of bounds
  if (food.point.x > gridSize.GetWidth() ||
      food.point.y > gridSize.GetHeight()) {
    PlaceFood();
  }
}
