#ifndef GAME_HPP
#define GAME_HPP
#include "JsonSerializer.hpp"
#include "Player.hpp"
#include "PlayerController.hpp"
#include "GameStatesManager.hpp"
#include "ConsoleView.hpp"

class Game {
 public:
  Game();
  void InitializeResources();
  void Run();

 private:
  GameStatesManager game_states_manager_;
  ConsoleView console_view_;
};

#endif //GAME_HPP
