#ifndef QUITCURRENTSTATECOMMAND_HPP
#define QUITCURRENTSTATECOMMAND_HPP
#include "../interfaces/ICommand.hpp"
#include "../GameStatesManager.hpp"

class QuitCurrentStateCommand : public ICommand {
 public:
  explicit QuitCurrentStateCommand(GameStatesManager &game_states_manager) : game_states_manager_{game_states_manager} {}
  void Execute() override {
	game_states_manager_.PopState();
  }

 private:
  GameStatesManager &game_states_manager_;
};

#endif //QUITCURRENTSTATECOMMAND_HPP
