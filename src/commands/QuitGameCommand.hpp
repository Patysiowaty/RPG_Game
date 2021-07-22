#ifndef QUITGAMECOMMAND_HPP
#define QUITGAMECOMMAND_HPP

#include "../interfaces/ICommand.hpp"
#include "../GameStatesManager.hpp"
class QuitGameCommand : public ICommand {
 public:
  explicit QuitGameCommand() {}

  void Execute() override {
	exit(EXIT_SUCCESS);
  }
};

#endif //QUITGAMECOMMAND_HPP
