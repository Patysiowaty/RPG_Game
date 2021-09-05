#ifndef WINDOWSMANAGER_HPP
#define WINDOWSMANAGER_HPP
#include <SFML/Window/Keyboard.hpp>
#include <map>
#include "../interfaces/IUpdatable.hpp"
#include "../interfaces/IGameWindow.hpp"
#include "../game_core/PlayerCamera.hpp"

enum class WindowTypes {
  kNone, kPlayerStatistics, kInventory, kEquipment, kJournal
};

class WindowsManager : public IUpdatable, public ICameraHandler {
 public:
  WindowsManager(const PlayerCamera &player_camera);
  void Update(float delta_time) override;
  void RegisterWindow(WindowTypes window_type, IGameWindow *game_window);

 private:
  const PlayerCamera &player_camera_;
  std::map<WindowTypes, IGameWindow *> windows_list_;
  std::map<sf::Keyboard::Key, WindowTypes> windows_key_bind_;
};

#endif //WINDOWSMANAGER_HPP
