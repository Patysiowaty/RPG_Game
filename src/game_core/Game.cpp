#include "Game.hpp"
#include "../MenuGameState.hpp"
#include "GameConfig.hpp"

const sf::Time Game::kTimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() {

}

void Game::InitializeResources() {
  game_states_manager_.PushState(std::make_shared<MenuGameState>(game_states_manager_));

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
  while (main_window_.isOpen() && !game_states_manager_.GetGameStatesPtr().empty()) {
	const auto current_state = game_states_manager_.GetGameStatesPtr().top();
	last_update_ += timer_.restart();
	sf::Event next_event;
	while (last_update_ > kTimePerFrame) {
	  last_update_ -= kTimePerFrame;
	  if (main_window_.pollEvent(next_event))
		current_state->HandleEvent(next_event);
	  current_state->Update(last_update_);
	  current_state->Render(main_window_);
	}
  }
}


