#include "Game.hpp"
#include "PlayGameState.hpp"

Game::Game() : run_{true} {
  game_states_manager_.PushState(std::make_unique<PlayGameState>());
}

void Game::InitializeResources() {

}

void Game::Run() {
  while (run_) {
	game_states_manager_.GetCurrentState()->HandleEvent();
	game_states_manager_.GetCurrentState()->Update(1);
	game_states_manager_.GetCurrentState()->Draw(1);
  }
  OnQuit();
}

void Game::OnQuit() {
}

void Game::Quit() {
  run_ = false;
}

