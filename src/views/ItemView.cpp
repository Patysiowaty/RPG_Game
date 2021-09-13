#include "ItemView.hpp"

ItemView::ItemView(const std::shared_ptr<Item> &item) : item_tip_view_{item} {
  FillData(item);
}

void ItemView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  Window::draw(target, states);
  if (tip_visible_)
	target.draw(item_tip_view_, states);
}

void ItemView::FillData(const std::shared_ptr<Item> &item) {
  const auto &icon = item->GetIconPath();
  Window::LoadWindowTexture("../resources/graphics/items/" + icon);
}

void ItemView::SetTipVisibility(bool visibility) {
  tip_visible_ = visibility;
}

void ItemView::Move(const sf::Vector2f &offset) {
  Window::Move(offset);
}

void ItemView::SetPosition(const sf::Vector2f &new_position) {
  Window::SetPosition(new_position);
}


