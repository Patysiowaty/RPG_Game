#ifndef IGAMEWINDOW_HPP
#define IGAMEWINDOW_HPP

#include <SFML/System/Vector2.hpp>

class WindowsManager;

class IGameWindow {
 public:
  ~IGameWindow() = default;
  virtual void OpenWindow() = 0;
  virtual void CloseWindow() = 0;
  virtual bool IsOpen() const = 0;
  virtual void Move(const sf::Vector2f &offset) = 0;
  virtual void RegisterManager(WindowsManager *windows_manager) = 0;
  virtual void ReloadData() = 0;
};

#endif //IGAMEWINDOW_HPP
