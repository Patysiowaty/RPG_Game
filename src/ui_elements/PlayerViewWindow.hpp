#ifndef PLAYERVIEWWINDOW_HPP
#define PLAYERVIEWWINDOW_HPP
#include "../views/PlayerView.hpp"
#include "Window.hpp"

class PlayerViewWindow : public Window {
 public:
  explicit PlayerViewWindow();

  void Update(float delta_time) override;
  void SetRelativeViewPosition(const sf::Vector2f &new_position);
  void SetPosition(const sf::Vector2f &new_position) override;
  void Move(const sf::Vector2f &offset) override;
  void EquipItem(const std::shared_ptr<Item> &item);
  void TakeOffItem(ItemType item_type);

 protected:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

 private:
  PlayerView player_view_;
  sf::Vector2f relative_view_position_{0.f, 0.f};
};

#endif //PLAYERVIEWWINDOW_HPP
