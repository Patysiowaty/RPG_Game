#ifndef LOADGAMESTATECOMMAND_HPP
#define LOADGAMESTATECOMMAND_HPP
#include "../interfaces/ICommand.hpp"
#include "../GameStatesManager.hpp"
#include "../interfaces/IGameState.hpp"

class LoadGameStateCommand : public ICommand {
 public:
  explicit LoadGameStateCommand(GameStatesManager &game_states_manager, std::shared_ptr<IGameState> game_state)
	  : game_states_manager_{game_states_manager}, game_state_{game_state} {}

  void Execute() override {
	game_states_manager_.PushState(game_state_);
  }

 private:
  GameStatesManager &game_states_manager_;
  std::shared_ptr<IGameState> game_state_;
};

#endif //LOADGAMESTATECOMMAND_HPP
