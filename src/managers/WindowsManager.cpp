#include "WindowsManager.hpp"
#include "InputManager.hpp"
WindowsManager::WindowsManager(PlayerController &player_controller)  {

}

void WindowsManager::Update(float delta_time) {
  for (const auto[first, second] : windows_key_bind_) {
	if (InputManager::IsKeyReleased(first)) break;

  }
}

void WindowsManager::OpenWindow(WindowTypes window_type) {

}

void WindowsManager::CloseWindow(WindowTypes window_type) {

}

