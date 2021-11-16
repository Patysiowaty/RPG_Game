#include "PlayGameState.hpp"
#include "../JsonSerializer.hpp"
PlayGameState::PlayGameState(GameStatesManager &game_states_manager, sf::RenderWindow &render_window)
	: game_states_manager_{game_states_manager}, render_window_{render_window},
	  player_controller_{player_, player_view_}, inventory_window_{player_controller_, "Inventory"},
	  character_stats_window_{player_controller_, "Statistics"} {
}

void PlayGameState::Initialize() {
  ReadConfigs();
  RegisterHandlers();
  LoadGameData();
  LoadTextures();
  SetObjectsPosition();
  character_stats_window_.OnInit();
  inventory_window_.OnInit();

  character_stats_window_.SetPosition({500, 100});
  inventory_window_.Move({100, 100});
}

void PlayGameState::Render() {
  if (!active_) return;
  //render_window_.setView(game_camera_);
  render_window_.clear();
  drawable_container_.Draw(render_window_);
}

void PlayGameState::Update(const float delta_time) {
  if (!active_) return;
  for (auto &updatable: updatable_list_)
	updatable->Update(delta_time);
}

void PlayGameState::Cleanup() {

}

void PlayGameState::Pause() {
  active_ = false;
}

void PlayGameState::Resume() {
  active_ = true;
}

void PlayGameState::Reload(const GameConfig &config) {

}

void PlayGameState::RegisterHandlers() {
  player_controller_.RegisterHandler(&game_camera_);

  updatable_list_.emplace_back(&windows_manager_);
  updatable_list_.emplace_back(&player_controller_);
  updatable_list_.emplace_back(&battle_system_);
  updatable_list_.emplace_back(&player_view_);
  updatable_list_.emplace_back(&inventory_window_);
  updatable_list_.emplace_back(&character_stats_window_);

  drawable_container_.AddDrawable(0, &current_player_location_);
  drawable_container_.AddDrawable(1, &player_view_);
  drawable_container_.AddDrawable(10, &inventory_window_);
  drawable_container_.AddDrawable(10, &character_stats_window_);

  windows_manager_.RegisterWindow(WindowTypes::kInventory, &inventory_window_);
  windows_manager_.RegisterWindow(WindowTypes::kPlayerStatistics, &character_stats_window_);
}

void PlayGameState::SetObjectsPosition() {
  player_view_.SetPosition(player_.getPosition().x, player_.getPosition().y);
  game_camera_.setCenter(player_.getPosition().x, player_.getPosition().y);
}

void PlayGameState::LoadTextures() {
  player_view_.CreateSprite("../resources/graphics/player.png");
  current_player_location_.LoadMapTexture("../resources/graphics/map.png");
}

void PlayGameState::ReadConfigs() {
  JSONSerializer json_serializer;

  GameConfig game_config;
  json_serializer.Deserialize(game_config, "../configs/game_config.json");
}

void PlayGameState::LoadGameData() {
  JSONSerializer json_serializer;
  json_serializer.Deserialize(player_, "../game_data/player_data.json");
}

