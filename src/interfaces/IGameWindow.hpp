#ifndef IGAMEWINDOW_HPP
#define IGAMEWINDOW_HPP

class IGameWindow {
 public:
  ~IGameWindow() = default;
  virtual void OpenWindow() = 0;
  virtual void CloseWindow() = 0;
  virtual bool IsOpen() const = 0;
};

#endif //IGAMEWINDOW_HPP
