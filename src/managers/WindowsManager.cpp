#include "WindowsManager.hpp"
#include "InputManager.hpp"
#include "../commands/CloseWindowCommand.hpp"
#include "../commands/OpenWindowCommand.hpp"
WindowsManager::WindowsManager(const PlayerCamera &player_camera) : player_camera_{player_camera} {
  windows_key_bind_.emplace(sf::Keyboard::I, WindowTypes::kInventory);
}

void WindowsManager::Update(float delta_time) {
  for (const auto&[first, second] : windows_key_bind_) {
	if (InputManager::IsKeyReleased(first)) {
	  auto &wnd = windows_list_.at(second);
	  if (wnd->IsOpen())
		std::make_unique<CloseWindowCommand>(*wnd)->Execute();
	  else {
		std::make_unique<OpenWindowCommand>(*wnd)->Execute();
	  }
	}
  }
}

void WindowsManager::RegisterWindow(WindowTypes window_type, IGameWindow *game_window) {
  windows_list_.emplace(window_type, game_window);
}

