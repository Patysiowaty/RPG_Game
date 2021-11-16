#ifndef CHANGEINVENTORYTABCOMMAND_HPP
#define CHANGEINVENTORYTABCOMMAND_HPP

#include "../interfaces/ICommand.hpp"
#include "../ui_elements/InventoryWindow.hpp"
#include "../enums/DirectionCommand.hpp"
class ChangeInventoryTabCommand : public ICommand {
 public:
  explicit ChangeInventoryTabCommand(InventoryWindow &inventory_window, DirectionCommand direction) : inventory_window_{
	  inventory_window}, direction_command_{direction} {}

  void Execute() override {
	if (direction_command_ == DirectionCommand::kNext)
	  inventory_window_.ShowNextTab();
	else if (direction_command_ == DirectionCommand::kBack)
	  inventory_window_.ShowPreviousTab();
  }

 private:
  InventoryWindow &inventory_window_;
  DirectionCommand direction_command_{DirectionCommand::kNone};
};

#endif //CHANGEINVENTORYTABCOMMAND_HPP
