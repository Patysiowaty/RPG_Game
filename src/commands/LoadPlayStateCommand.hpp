#ifndef LOADPLAYSTATECOMMAND_HPP
#define LOADPLAYSTATECOMMAND_HPP
#include "../GameStatesManager.hpp"
#include "../PlayGameState.hpp"

class LoadPlayStateCommand : public ICommand {
 public:
  LoadPlayStateCommand(GameStatesManager &game_states_manager) : game_states_manager_{game_states_manager} {}
  void Execute() override {
	game_states_manager_.PushState(std::make_unique<PlayGameState>(game_states_manager_));
  }

 private:
  GameStatesManager &game_states_manager_;
};

#endif //LOADPLAYSTATECOMMAND_HPP
