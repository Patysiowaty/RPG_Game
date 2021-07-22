#include "GameStatesManager.hpp"
void GameStatesManager::PushState(std::unique_ptr<IGameState> game_state) {
  if (!states_.empty())
	states_.top()->Pause();
  states_.emplace(std::move(game_state));
  states_.top()->Initialize();
}

void GameStatesManager::PopState() {
  if (states_.empty()) return;

  states_.top()->Cleanup();
  states_.pop();

  if (!states_.empty())
	states_.top()->Resume();
}

const std::unique_ptr<IGameState> &GameStatesManager::GetCurrentState() {
  return states_.top();
}

