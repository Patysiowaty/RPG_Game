#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "../JsonSerializer.hpp"
#include "../models/Player.hpp"
#include "../controllers/PlayerController.hpp"
#include "../managers/GameStatesManager.hpp"
#include "../managers/InputManager.hpp"

class Game {
 public:
  Game() = default;
  void InitializeResources();
  void Run();

 private:
  void HandleIncomingInput();

 private:
  static const sf::Time kTimePerFrame;

  GameStatesManager game_states_manager_;
  sf::RenderWindow main_window_;
  InputManager input_manager_;
};

#endif //GAME_HPP
