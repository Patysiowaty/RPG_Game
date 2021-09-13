#ifndef INVENTORYWINDOW_HPP
#define INVENTORYWINDOW_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Window.hpp"
#include "../views/ItemView.hpp"
#include "../interfaces/IGameWindow.hpp"
#include "../models/Player.hpp"
#include "../SlotIndex.hpp"
#include "ItemSlot.hpp"
#include "Button.hpp"

class InventoryWindow : public Window, public IGameWindow {
 public:
  explicit InventoryWindow(Player &player, const std::string &wnd_name = "");

  void Deserialize(const boost::property_tree::ptree &ptree) override;
  void OpenWindow() override;
  void CloseWindow() override;
  void Update(float delta_time) override;
  void Move(const sf::Vector2f &offset) override;
  void PlaceItem(const std::shared_ptr<Item> &item, const SlotIndex &slot_index);
  void RemoveItem(const SlotIndex &slot_index);
  void OnChildrenWindowEvent(Window *sender, WindowEvent event_type) override;
  bool IsOpen() const override { return Window::IsVisible(); }
  const sf::Vector2f &GetWindowSize() const override { return Window::GetRectangleShape().getSize(); }

 private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void CreateSlots();
  void PlaceSlots();
  void PlaceItems();
  void RemoveItems();
  void InitializeWndComponents();
  void InitializeButtons();

 private:
  Player &player_;

  const int kRowItemCount{5};
  const int kColumnItemCount{7};
  const sf::IntRect kSlotSizeSpritePosition{216, 0, 36, 36};
  const sf::IntRect kCloseButtonSpritePosition{240, 38, 10, 10};
  const sf::IntRect kInventoryWndSpritePosition{0, 0, 214, 338};

  sf::Text window_name_text_;
  sf::Font font_;
  std::map<SlotIndex, ItemSlot> items_slots_;
  sf::RectangleShape draggable_trigger_;
  std::vector<Button> inventory_tabs_;
  Button close_btn_;
  Button next_tab_btn_;
  Button previous_tab_btn_;
};

#endif //INVENTORYWINDOW_HPP
