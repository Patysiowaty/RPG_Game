#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "../JsonSerializer.hpp"
#include "Player.hpp"
#include "PlayerController.hpp"
#include "../GameStatesManager.hpp"

class Game {
 public:
  Game();
  void InitializeResources();
  void Run();

 private:
  sf::Event GetUserInput();

 private:
  static const sf::Time kTimePerFrame;

  GameStatesManager game_states_manager_;
  sf::RenderWindow main_window_;
  sf::Clock timer_;
  sf::Time last_update_ = sf::Time::Zero;
};

#endif //GAME_HPP
