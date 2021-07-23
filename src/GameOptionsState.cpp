#include "GameOptionsState.hpp"
#include "JsonSerializer.hpp"
#include "game_core/GameConfig.hpp"
#include "commands/QuitCurrentStateCommand.hpp"

GameOptionsState::GameOptionsState(GameStatesManager &game_states_manager) : game_states_manager_{game_states_manager} {

}

void GameOptionsState::Initialize() {
  JSONSerializer json_serializer;
  GameConfig game_config;
  json_serializer.Deserialize(game_config, "../configs/game_config.json");

  event_dispatcher_.RegisterHandler(&return_button_);

  return_button_.AddCommand(CommandInvoker::kLeftMouseButtonClick,
							std::make_unique<QuitCurrentStateCommand>(game_states_manager_));

  game_option_font_.loadFromFile("../resources/fonts/ZenLoop-Regular.ttf");
  return_button_.CreateText("Return", game_option_font_, 34);
  return_button_.CreateSprite("../resources/graphics/button_menu.png", {0, 0, 256, 64});

  const float kLeftPosition = (game_config.window_size_.x - 256.f) / 2.f;
  const float kTopPosition = (game_config.window_size_.y - 64.f) * .75f;

  return_button_.SetPosition({kLeftPosition, kTopPosition});
}

void GameOptionsState::Render(sf::RenderWindow &window) {
  window.clear({0, 100, 20});
  return_button_.Render(window);
}

void GameOptionsState::Update(sf::Time delta_time) {

}

void GameOptionsState::HandleEvent(const sf::Event &event) {
  event_dispatcher_.DispatchEvent(event);
}

void GameOptionsState::Cleanup() {

}

void GameOptionsState::Pause() {
  active_ = false;
}

void GameOptionsState::Resume() {
  active_ = true;
}

