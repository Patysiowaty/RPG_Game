#include "OptionGameState.hpp"
#include "JsonSerializer.hpp"
#include "game_core/GameConfig.hpp"

OptionGameState::OptionGameState(GameStatesManager &game_states_manager) : game_states_manager_{game_states_manager} {

}

void OptionGameState::Initialize() {
  JSONSerializer json_serializer;
  GameConfig game_config;
  json_serializer.Deserialize(game_config, "../game_data/test.json");
}

void OptionGameState::Render(sf::RenderWindow &window) {

}
void OptionGameState::Update(sf::Time delta_time) {

}
void OptionGameState::HandleEvent(const sf::Event &event) {

}
void OptionGameState::Cleanup() {

}
void OptionGameState::Pause() {
  active_ = false;
}

void OptionGameState::Resume() {
  active_ = true;
}

