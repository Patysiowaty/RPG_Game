#include "Game.hpp"
#include "PlayGameState.hpp"

Game::Game() {
  game_states_manager_.PushState(std::make_unique<PlayGameState>(game_states_manager_));
}

void Game::InitializeResources() {

}

void Game::Run() {
  while (true) {
	game_states_manager_.GetCurrentState()->HandleEvent();
	game_states_manager_.GetCurrentState()->Update(1);
	game_states_manager_.GetCurrentState()->Draw(&console_view_, 1);
  }
}


