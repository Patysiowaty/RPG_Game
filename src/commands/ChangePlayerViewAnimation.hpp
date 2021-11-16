#ifndef CHANGEPLAYERVIEWANIMATION_HPP
#define CHANGEPLAYERVIEWANIMATION_HPP
#include "../interfaces/ICommand.hpp"
#include "../ui_elements/PlayerViewWindow.hpp"
#include "../enums/DirectionCommand.hpp"

class ChangePlayerViewAnimation : public ICommand {
 public:
  explicit ChangePlayerViewAnimation(PlayerViewWindow &player_view_window, DirectionCommand direction)
	  : player_view_window_{player_view_window}, direction_command_{direction} {}

  void Execute() override {
	if (direction_command_ == DirectionCommand::kBack)
	  player_view_window_.PreviousAnimation();
	else
	  player_view_window_.NextAnimation();
  }

 private:
  PlayerViewWindow &player_view_window_;
  DirectionCommand direction_command_;
};

#endif //CHANGEPLAYERVIEWANIMATION_HPP
