#ifndef CLOSEWINDOWCOMMAND_HPP
#define CLOSEWINDOWCOMMAND_HPP

#include "../interfaces/ICommand.hpp"
#include "../interfaces/IGameWindow.hpp"
class CloseWindowCommand : public ICommand {
 public:
  explicit CloseWindowCommand(IGameWindow &game_window) : game_window_{game_window} {}
  void Execute() override { game_window_.CloseWindow(); }

 private:
  IGameWindow &game_window_;
};

#endif //CLOSEWINDOWCOMMAND_HPP
