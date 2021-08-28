#include "Game.hpp"
#include "../game_states/MenuGameState.hpp"
#include "../game_states/PlayGameState.hpp"

const sf::Time Game::kTimePerFrame = sf::seconds(1.f / 60.f);

void Game::InitializeResources() {
  game_states_manager_.PushState(std::make_shared<MenuGameState>(game_states_manager_, main_window_));
  //game_states_manager_.PushState(std::make_shared<PlayGameState>(game_states_manager_, main_window_));

  JSONSerializer serializer;
  GameConfig config;
  serializer.Deserialize(config, "../configs/game_config.json");
  //const auto &desktop_mode = sf::VideoMode::getDesktopMode();
  main_window_.create(sf::VideoMode{config.window_size_.x, config.window_size_.y},
					  config.window_title_, config.style_, config.context_settings_);
  main_window_.setVerticalSyncEnabled(config.window_v_sync_);
  //TODO: Add icon
/*  sf::Image image;
  image.loadFromFile(configs.window_icon_path_);
  main_window_.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());*/
}

void Game::Run() {
  sf::Clock timer;
  while (main_window_.isOpen() && !game_states_manager_.GetGameStatesPtr().empty()) {
	auto delta_time = timer.restart();
	const auto current_state = game_states_manager_.GetGameStatesPtr().top();
	HandleIncomingInput();
	while (delta_time <= kTimePerFrame) {
	  current_state->Update(delta_time.asSeconds());
	  delta_time += kTimePerFrame;
	}
	current_state->Render();
	main_window_.display();
  }
}

void Game::HandleIncomingInput() {
  sf::Event event;
  if (main_window_.pollEvent(event)) {
	if (event.type == sf::Event::Closed) {
	  game_states_manager_.GetGameStatesPtr().top()->Pause();
	  game_states_manager_.GetGameStatesPtr().top()->Cleanup();
	  main_window_.close();
	} else if (event.type == sf::Event::LostFocus) {
	  game_states_manager_.GetGameStatesPtr().top()->Pause();
	} else if (event.type == sf::Event::GainedFocus) {
	  game_states_manager_.GetGameStatesPtr().top()->Resume();
	}
  }
  input_manager_.RegisterNextInput(event);
}


