#ifndef SHOWMORESTATISTICSCOMMAND_HPP
#define SHOWMORESTATISTICSCOMMAND_HPP
#include "../ui_elements/PlayerStatsWindow.hpp"
#include "../interfaces/ICommand.hpp"
class ShowMoreStatisticsCommand : public ICommand {
 public:
  explicit ShowMoreStatisticsCommand(PlayerStatsWindow &player_stats_window) : player_stats_window_{
	  player_stats_window} {}

  void Execute() override {
	player_stats_window_.ShowMoreStats();
  }

 private:
  PlayerStatsWindow &player_stats_window_;
};

#endif //SHOWMORESTATISTICSCOMMAND_HPP
