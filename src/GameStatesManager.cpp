#include "GameStatesManager.hpp"
void GameStatesManager::PushState(std::shared_ptr<IGameState> game_state) {
  if (!states_.empty())
	states_.top()->Pause();
  states_.emplace(std::move(game_state));
  states_.top()->Initialize();
}

void GameStatesManager::PopState() {
  if (states_.empty()) return;
  states_.top()->Pause();
  states_.top()->Cleanup();
  states_.pop();

  if (!states_.empty())
	states_.top()->Resume();
}

const GameStatesManager::GameStatesPtr &GameStatesManager::GetGameStatesPtr() const {
  return states_;
}

void GameStatesManager::ClearStack() {
  while (!states_.empty()) {
	states_.top()->Pause();
	states_.top()->Cleanup();
	states_.pop();
  }
}

