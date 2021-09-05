#include "GameOptionsState.hpp"
#include "../commands/QuitCurrentStateCommand.hpp"
#include "../JsonSerializer.hpp"

GameOptionsState::GameOptionsState(GameStatesManager &game_states_manager, sf::RenderWindow &render_window)
	: game_states_manager_{game_states_manager}, render_window_{render_window} {

}

void GameOptionsState::Initialize() {
  JSONSerializer json_serializer;
  GameConfig game_config;
  json_serializer.Deserialize(game_config, "../configs/game_config.json");

  return_button_.AddCommand(CommandInvoker::kLeftMouseButtonClick,
							std::make_unique<QuitCurrentStateCommand>(game_states_manager_));

}

void GameOptionsState::Render() {
  render_window_.clear(sf::Color::Blue);
  render_window_.draw(return_button_);
}

void GameOptionsState::Update(const float delta_time) {

}

void GameOptionsState::Cleanup() {

}

void GameOptionsState::Pause() {
  active_ = false;
}

void GameOptionsState::Resume() {
  active_ = true;
}

void GameOptionsState::Reload(const GameConfig &game_config) {
  const float kLeftPosition = (game_config.window_size_.x - 256.f) / 2.f;
  const float kTopPosition = (game_config.window_size_.y - 64.f) * .75f;

  return_button_.SetPosition({kLeftPosition, kTopPosition});
}

