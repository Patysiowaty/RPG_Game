#include "PlayGameState.hpp"
#include "JsonSerializer.hpp"
PlayGameState::PlayGameState(GameStatesManager &game_states_manager) : game_states_manager_{game_states_manager},
																	   player_controller_{player_} {
}

void PlayGameState::Initialize() {

}

void PlayGameState::Draw(IViewContext *view_context, double delta_time) {

}

void PlayGameState::Update(double delta_time) {
  battle_system_.Update();
}

void PlayGameState::HandleEvent() {

}

void PlayGameState::Cleanup() {

}

void PlayGameState::Pause() {
  active_ = false;
}

void PlayGameState::Resume() {
  active_ = true;
}

