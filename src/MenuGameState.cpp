#include "MenuGameState.hpp"
#include "game_core/GameConfig.hpp"
#include "commands/QuitGameCommand.hpp"
#include "commands/LoadGameStateCommand.hpp"
#include "commands/ChangeGameStateCommand.hpp"
#include "GameOptionsState.hpp"
#include "PlayGameState.hpp"

MenuGameState::MenuGameState(GameStatesManager &game_states_manager) : game_states_manager_{game_states_manager} {

}

void MenuGameState::Initialize() {
  start_game_button_.AddCommand(CommandInvoker::kLeftMouseButtonClick,
								std::make_unique<ChangeGameStateCommand>(game_states_manager_,
																		 std::make_shared<PlayGameState>(
																			 game_states_manager_)));

  game_option_button_.AddCommand(CommandInvoker::kLeftMouseButtonClick,
								 std::make_unique<LoadGameStateCommand>(game_states_manager_,
																		std::make_shared<GameOptionsState>(
																			game_states_manager_)));

  quit_game_button_.AddCommand(CommandInvoker::kLeftMouseButtonClick,
							   std::make_unique<QuitGameCommand>(game_states_manager_));

  event_dispatcher_.RegisterHandler(&start_game_button_);
  event_dispatcher_.RegisterHandler(&load_game_button_);
  event_dispatcher_.RegisterHandler(&game_option_button_);
  event_dispatcher_.RegisterHandler(&quit_game_button_);

  GameConfig game_config;
  JSONSerializer serializer;
  serializer.Deserialize(game_config, "../configs/game_config.json");

  menu_state_font_.loadFromFile("../resources/fonts/ZenLoop-Regular.ttf");

  start_game_button_.CreateText("Start game", menu_state_font_, 42);
  load_game_button_.CreateText("Load game", menu_state_font_, 42);
  game_option_button_.CreateText("Options", menu_state_font_, 42);
  quit_game_button_.CreateText("Quit game", menu_state_font_, 42);

  start_game_button_.CreateSprite("../resources/graphics/button_menu.png", {0, 0, 256, 64});
  load_game_button_.CreateSprite("../resources/graphics/button_menu.png", {0, 0, 256, 64});
  game_option_button_.CreateSprite("../resources/graphics/button_menu.png", {0, 0, 256, 64});
  quit_game_button_.CreateSprite("../resources/graphics/button_menu.png", {0, 0, 256, 64});

  const float kLeftPosition = (game_config.window_size_.x - 256.f) / 2.f;
  const float kInitialTopPosition = (game_config.window_size_.y - 64.f) / 3.f;
  const float kButtonDistanceFactor = 100.f;

  start_game_button_.SetPosition({kLeftPosition, kInitialTopPosition});
  load_game_button_.SetPosition({kLeftPosition, kInitialTopPosition + kButtonDistanceFactor});
  game_option_button_.SetPosition({kLeftPosition, kInitialTopPosition + 2 * kButtonDistanceFactor});
  quit_game_button_.SetPosition({kLeftPosition, kInitialTopPosition + 3 * kButtonDistanceFactor});
}

void MenuGameState::Render(sf::RenderWindow &window) {
  if (!active_) return;
  window.clear({100,20,0});
  start_game_button_.Render(window);
  load_game_button_.Render(window);
  game_option_button_.Render(window);
  quit_game_button_.Render(window);
}

void MenuGameState::Update(sf::Time delta_time) {
  if (!active_) return;
  start_game_button_.Update(delta_time);
  load_game_button_.Update(delta_time);
  game_option_button_.Update(delta_time);
  quit_game_button_.Update(delta_time);
}

void MenuGameState::HandleEvent(const sf::Event &event) {
  if (!active_) return;
  event_dispatcher_.DispatchEvent(event);
}

void MenuGameState::Cleanup() {

}

void MenuGameState::Pause() {
  active_ = false;
}

void MenuGameState::Resume() {
  active_ = true;
}

