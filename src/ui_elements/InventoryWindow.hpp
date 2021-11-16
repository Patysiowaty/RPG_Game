#ifndef INVENTORYWINDOW_HPP
#define INVENTORYWINDOW_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Window.hpp"
#include "../views/ItemView.hpp"
#include "../interfaces/IGameWindow.hpp"
#include "../SlotIndex.hpp"
#include "ItemSlot.hpp"
#include "Button.hpp"
#include "../controllers/PlayerController.hpp"

class InventoryWindow : public Window, public IGameWindow {
 public:
  explicit InventoryWindow(PlayerController &player_controller, const std::string &wnd_name = "");

  void OnInit();
  void Deserialize(const boost::property_tree::ptree &ptree) override;
  void Update(float delta_time) override;
  void SetPosition(const sf::Vector2f &new_position) override;
  void Move(const sf::Vector2f &offset) override;
  void OnChildrenWindowEvent(Window *sender, WindowEvent event_type) override;
  void OpenWindow() override;
  void CloseWindow() override;
  bool IsOpen() const override { return Window::IsVisible(); }
  void RegisterManager(WindowsManager *windows_manager) override;
  void ReloadData() override;

  void RemoveItem(const SlotIndex &slot_index);
  void PlaceItem(const std::shared_ptr<Item> &item, const SlotIndex &slot_index);
  void ShowNextTab();
  void ShowPreviousTab();
  void ShowConcreteTab(std::uint16_t value);

 private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void CreateSlots();
  void PlaceSlots();
  void PlaceItemsInSlots();
  void SetButtons();
  void SetTabButton(Button &button, int number);
  void SetCloseButton(Button &button);
  void SetKeyTabButton(Button &button);

  void RemoveItems();

 private:
  PlayerController &player_controller_;
  WindowsManager *windows_manager_{nullptr};

  enum class ButtonType {
	kClose, kNextTab, kPreviousTab, kTab1, kTab2, kTab3, kTab4, kKeyTab, kSize = 8
  };

  sf::Font font_;
  Label wnd_name_;
  std::uint16_t active_tab_{0};
  std::map<SlotIndex, ItemSlot> items_slots_;
  std::map<ButtonType, Button> buttons_list_;
};

#endif //INVENTORYWINDOW_HPP
