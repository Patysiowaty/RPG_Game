#ifndef OPENWINDOWCOMMAND_HPP
#define OPENWINDOWCOMMAND_HPP

#include "../interfaces/ICommand.hpp"
#include "../interfaces/IGameWindow.hpp"
class OpenWindowCommand : public ICommand {
 public:
  explicit OpenWindowCommand(IGameWindow &game_window) : game_window_{game_window} {}
  void Execute() override { game_window_.OpenWindow(); }

 private:
  IGameWindow &game_window_;
};

#endif //OPENWINDOWCOMMAND_HPP
