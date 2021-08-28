#include "WindowsManager.hpp"
#include "InputManager.hpp"
WindowsManager::WindowsManager(PlayerController &player_controller) : player_controller_{player_controller} {

}

void WindowsManager::Update(float delta_time) {
  for (const auto[first, second] : windows_key_bind_) {
	if (InputManager::IsKeyReleased(first)) break;

  }
}

void WindowsManager::Render(sf::RenderWindow &render_window) {
  if (!windows_list_.empty()) {
	for (const auto&[first, second]: windows_list_) {
	  if (second.IsVisible())
		render_window.draw(second);
	}
  }
}

void WindowsManager::OpenWindow(WindowTypes window_type) {

}

void WindowsManager::CloseWindow(WindowTypes window_type) {
}

void WindowsManager::Deserialize(const boost::property_tree::ptree &ptree) {

}

void WindowsManager::OnPlayerMove(const sf::Vector2<float> &offset) {

}

