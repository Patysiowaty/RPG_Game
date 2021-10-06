#ifndef PLAYERSTATSWINDOW_HPP
#define PLAYERSTATSWINDOW_HPP

#include "Window.hpp"
#include "ItemSlot.hpp"
#include "Label.hpp"
#include "Button.hpp"
#include "PlayerViewWindow.hpp"
#include "../controllers/PlayerController.hpp"

class PlayerStatsWindow : public Window, public IGameWindow {
 public:
  explicit PlayerStatsWindow(PlayerController &player_controller, const std::string &window_name);

  void Deserialize(const boost::property_tree::ptree &ptree) override;
  void Update(float delta_time) override;
  void Move(const sf::Vector2f &offset) override;
  void SetPosition(const sf::Vector2f &new_position) override;
  void OnChildrenWindowEvent(Window *sender, WindowEvent event_type) override;
  void OpenWindow() override;
  void CloseWindow() override;
  bool IsOpen() const override;
  const sf::Vector2f &GetWindowSize() const override;
  void OnInit();
  void RemoveItem(ItemType item_type);
  void RegisterManager(WindowsManager *windows_manager) override;
  void ReloadData() override;

 private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  void CreateLabels();
  void SetLabels();
  void CreateEquipmentSlots();
  void FillValueLabelsData();
  void SetButtons();
  void SetPlayerView();
  void SetValueLabelsData();
  void FillEquipmentSlots();

 private:
  PlayerController &player_controller_;
  WindowsManager *windows_manager_{nullptr};

  sf::Font font_;

  sf::RectangleShape draggable_trigger_;
  std::map<ItemType, ItemSlot> equipment_slots_list_;
  std::map<AttributeType, Label> attribute_text_labels_;
  std::map<AttributeType, Label> attribute_value_labels_;
  std::map<StatisticType, Label> statistic_text_labels_;
  std::map<StatisticType, Label> statistic_value_labels_;

  Label wnd_name_;
  Label character_name_label_;
  Button close_button_;
  PlayerViewWindow player_view_window_;
};

#endif //PLAYERSTATSWINDOW_HPP
