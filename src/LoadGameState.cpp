#include "LoadGameState.hpp"

LoadGameState::LoadGameState(GameStatesManager &game_states_manager) : game_states_manager_{game_states_manager} {

}

void LoadGameState::Initialize() {

}

void LoadGameState::Render(sf::RenderWindow &window) {

}

void LoadGameState::Update(sf::Time delta_time) {

}

void LoadGameState::HandleEvent(const sf::Event &event) {
  event_dispatcher_.DispatchEvent(event);
}

void LoadGameState::Cleanup() {

}

void LoadGameState::Pause() {

}

void LoadGameState::Resume() {

}

