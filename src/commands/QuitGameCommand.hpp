#ifndef QUITGAMECOMMAND_HPP
#define QUITGAMECOMMAND_HPP

#include "../interfaces/ICommand.hpp"
#include "../managers/GameStatesManager.hpp"
class QuitGameCommand : public ICommand {
 public:
  explicit QuitGameCommand(GameStatesManager &game_states_manager) : game_states_manager_{game_states_manager} {}

  void Execute() override {
	game_states_manager_.ClearStack();
  }

 private:
  GameStatesManager &game_states_manager_;
};

#endif //QUITGAMECOMMAND_HPP
