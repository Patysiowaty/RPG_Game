#include "PlayGameState.hpp"
#include "JsonSerializer.hpp"
PlayGameState::PlayGameState(GameStatesManager &game_states_manager) : game_states_manager_{game_states_manager},
																	   player_controller_{player_} {
}

void PlayGameState::Initialize() {
  JSONSerializer json_serializer;
  json_serializer.Deserialize(player_, "../game_data/test.json");
}

void PlayGameState::Render(sf::RenderWindow &window) {
  window.clear();
  window.display();
}

void PlayGameState::Update(sf::Time delta_time) {
  battle_system_.Update();
}

void PlayGameState::HandleEvent(const sf::Event &event) {

}

void PlayGameState::Cleanup() {

}

void PlayGameState::Pause() {
  active_ = false;
}

void PlayGameState::Resume() {
  active_ = true;
}

