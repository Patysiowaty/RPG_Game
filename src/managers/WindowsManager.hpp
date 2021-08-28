#ifndef WINDOWSMANAGER_HPP
#define WINDOWSMANAGER_HPP
#include <SFML/Window/Keyboard.hpp>
#include "../ui_elements/Window.hpp"
#include "../controllers/PlayerController.hpp"
#include "../interfaces/IUpdatable.hpp"

enum class WindowTypes {
  kNone, kStatistics, kInventory, kEquipment, kJournal
};

class WindowsManager : public IUpdatable {
 public:
  explicit WindowsManager(PlayerController &player_controller);
  void Update(float delta_time) override;
  void OpenWindow(WindowTypes window_type);
  void CloseWindow(WindowTypes window_type);

 private:
  std::map<WindowTypes, Window> windows_list_;
  std::map<sf::Keyboard::Key, WindowTypes> windows_key_bind_;
};

#endif //WINDOWSMANAGER_HPP
