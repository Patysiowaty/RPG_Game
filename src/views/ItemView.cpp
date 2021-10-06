#include "ItemView.hpp"
#include "../managers/InputManager.hpp"

ItemView::ItemView(const std::shared_ptr<Item> &item) : item_tip_view_{item} {
  if (!item) throw std::invalid_argument{"ItemView::ItemView -> nullptr item"};
  FillData(item);
}

void ItemView::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  Window::draw(target, states);
  if (item_tip_view_.IsVisible())
	target.draw(item_tip_view_, states);
}

void ItemView::FillData(const std::shared_ptr<Item> &item) {
  const auto &icon = item->GetIconPath();
  Window::LoadWindowTexture("../resources/graphics/items/" + icon);
  item_id_ = item->GetItemId();
}

void ItemView::Move(const sf::Vector2f &offset) {
  Window::Move(offset);
}

void ItemView::SetPosition(const sf::Vector2f &new_position) {
  Window::SetPosition(new_position);
}

void ItemView::Update(float delta_time) {
  Window::Update(delta_time);
  const auto &window_pos = Window::GetRectangleShape().getGlobalBounds();
  if (InputManager::IsMouseOver(window_pos)) {
	item_tip_view_.SetVisible(true);
	item_tip_view_.SetPosition(InputManager::GetMousePosition());
  } else
	item_tip_view_.SetVisible(false);

}
