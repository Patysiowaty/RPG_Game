#ifndef SHOWCONCRETEINVENTORYTABCOMMAND_HPP
#define SHOWCONCRETEINVENTORYTABCOMMAND_HPP
#include "../interfaces/ICommand.hpp"
#include "../ui_elements/InventoryWindow.hpp"

class ShowConcreteInventoryTabCommand : public ICommand {
 public:
  ShowConcreteInventoryTabCommand(InventoryWindow &window, std::uint16_t tab_index) : inventory_window_{
	  window}, tab_index_{tab_index} {}

  void Execute() override {
	inventory_window_.ShowConcreteTab(tab_index_);
  }

 private:
  InventoryWindow &inventory_window_;
  std::uint16_t tab_index_{0};
};

#endif //SHOWCONCRETEINVENTORYTABCOMMAND_HPP
