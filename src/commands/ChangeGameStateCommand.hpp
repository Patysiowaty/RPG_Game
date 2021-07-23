#ifndef CHANGEGAMESTATECOMMAND_HPP
#define CHANGEGAMESTATECOMMAND_HPP
#include "../interfaces/ICommand.hpp"
#include "../GameStatesManager.hpp"
#include "../interfaces/IGameState.hpp"

class ChangeGameStateCommand : public ICommand {
 public:
  explicit ChangeGameStateCommand(GameStatesManager &game_states_manager, std::shared_ptr<IGameState> game_state)
	  : game_states_manager_{game_states_manager}, game_state_{game_state} {}

  void Execute() override {
	game_states_manager_.PopState();
	game_states_manager_.PushState(game_state_);
  }

 private:
  GameStatesManager &game_states_manager_;
  std::shared_ptr<IGameState> game_state_;
};

#endif //CHANGEGAMESTATECOMMAND_HPP
