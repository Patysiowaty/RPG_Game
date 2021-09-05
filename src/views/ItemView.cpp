#include "ItemView.hpp"
#include <SFML/Graphics/RenderTarget.hpp>

ItemView::ItemView(const std::shared_ptr<Item> &item) {
  FillData(item);
}

void ItemView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= sprite_.getTransform();
  target.draw(sprite_, states);
  if (!tip_visible_) return;
}

void ItemView::FillData(const std::shared_ptr<Item> &item) {
  const auto &icon_path = item->GetIconPath();
  item_texture_.loadFromFile(icon_path);
}

void ItemView::SetTipVisibility(bool visibility) {
  tip_visible_ = visibility;
}

void ItemView::Move(const sf::Vector2f &offset) {
  transform_.move(offset);
  sprite_.move(offset);
}

void ItemView::SetPosition(const sf::Vector2f &new_position) {
  transform_.setPosition(new_position);
  sprite_.setPosition(new_position);
}


