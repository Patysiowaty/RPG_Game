#ifndef SHOWLESSSTATISTICSCOMMAND_HPP
#define SHOWLESSSTATISTICSCOMMAND_HPP
#include "../ui_elements/PlayerStatsWindow.hpp"
#include "../interfaces/ICommand.hpp"
class ShowLessStatisticsCommand : public ICommand {
 public:
  explicit ShowLessStatisticsCommand(PlayerStatsWindow &player_stats_window) : player_stats_window_{
	  player_stats_window} {}

  void Execute() override {
	player_stats_window_.ShowLessStats();
  }

 private:
  PlayerStatsWindow &player_stats_window_;
};

#endif //SHOWLESSSTATISTICSCOMMAND_HPP
