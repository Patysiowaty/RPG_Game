#include "MenuGameState.hpp"
#include "../commands/QuitGameCommand.hpp"
#include "../commands/LoadGameStateCommand.hpp"
#include "../commands/ChangeGameStateCommand.hpp"
#include "GameOptionsState.hpp"
#include "PlayGameState.hpp"
#include "../JsonSerializer.hpp"

MenuGameState::MenuGameState(GameStatesManager &game_states_manager, sf::RenderWindow &render_window)
	: game_states_manager_{game_states_manager}, render_window_{render_window} {
}

void MenuGameState::Initialize() {
  ReadConfigs();
  RegisterCommands();
  BindElements();
}

void MenuGameState::Render() {
  if (!active_) return;
  render_window_.clear({39, 35, 75});
  for (auto element : drawable_list_)
	render_window_.draw(*element);
}

void MenuGameState::Update(const float delta_time) {
  if (!active_) return;
  for (auto element : updatables_list_)
	element->Update(delta_time);
}

void MenuGameState::Cleanup() {

}

void MenuGameState::Pause() {
  active_ = false;
}

void MenuGameState::Resume() {
  active_ = true;
}

void MenuGameState::Reload(const GameConfig &config) {

}

void MenuGameState::RegisterCommands() {
  start_game_.AddCommand(CommandInvoker::kLeftMouseButtonClick,
						 std::make_unique<ChangeGameStateCommand>(game_states_manager_,
																  std::make_shared<PlayGameState>(
																	  game_states_manager_, render_window_)));

  game_options_.AddCommand(CommandInvoker::kLeftMouseButtonClick,
						   std::make_unique<LoadGameStateCommand>(game_states_manager_,
																  std::make_shared<GameOptionsState>(
																	  game_states_manager_, render_window_)));

  quit_game_.AddCommand(CommandInvoker::kLeftMouseButtonClick,
						std::make_unique<QuitGameCommand>(game_states_manager_));
}

void MenuGameState::BindElements() {
  drawable_list_.emplace_back(&start_game_);
  drawable_list_.emplace_back(&load_game_);
  drawable_list_.emplace_back(&game_options_);
  drawable_list_.emplace_back(&quit_game_);

  updatables_list_.emplace_back(&start_game_);
  updatables_list_.emplace_back(&load_game_);
  updatables_list_.emplace_back(&game_options_);
  updatables_list_.emplace_back(&quit_game_);
}

void MenuGameState::ReadConfigs() {
  JSONSerializer json_serializer;
  json_serializer.Deserialize(start_game_, "../configs/buttons_configs/menu_buttons_config.json", "startGame");
  json_serializer.Deserialize(load_game_, "../configs/buttons_configs/menu_buttons_config.json", "loadGame");
  json_serializer.Deserialize(game_options_, "../configs/buttons_configs/menu_buttons_config.json", "gameOptions");
  json_serializer.Deserialize(quit_game_, "../configs/buttons_configs/menu_buttons_config.json", "quitGame");
}

