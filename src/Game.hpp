#ifndef GAME_HPP
#define GAME_HPP
#include "JsonSerializer.hpp"
#include "Player.hpp"
#include "PlayerController.hpp"
#include "GameStatesManager.hpp"

class Game {
 public:
  Game();
  void InitializeResources();
  void Run();
  void Quit();

 private:
  void OnQuit();

 private:
  bool run_;
  GameStatesManager game_states_manager_;
};

#endif //GAME_HPP
