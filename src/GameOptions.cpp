#include "GameOptions.hpp"
#include "JsonSerializer.hpp"
#include "game_core/GameConfig.hpp"

GameOptions::GameOptions(GameStatesManager &game_states_manager) : game_states_manager_{game_states_manager} {

}

void GameOptions::Initialize() {
  JSONSerializer json_serializer;
  GameConfig game_config;
  json_serializer.Deserialize(game_config, "../game_data/test.json");
}

void GameOptions::Render(sf::RenderWindow &window) {

}
void GameOptions::Update(sf::Time delta_time) {

}
void GameOptions::HandleEvent(const sf::Event &event) {

}
void GameOptions::Cleanup() {

}
void GameOptions::Pause() {
  active_ = false;
}

void GameOptions::Resume() {
  active_ = true;
}

