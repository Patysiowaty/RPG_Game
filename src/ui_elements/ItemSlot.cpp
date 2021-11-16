#include "ItemSlot.hpp"
#include "../managers/InputManager.hpp"
ItemSlot::ItemSlot(Window *parent) : parent_{parent} {

}

void ItemSlot::PutItem(std::unique_ptr<ItemView> item_view) {
  item_view_ = std::move(item_view);
  item_view_->SetPosition(Window::GetRectangleShape().getPosition() + item_position_offset_);
}

void ItemSlot::TakeOutItem() { item_view_.reset(); }

void ItemSlot::Move(const sf::Vector2f &offset) {
  Window::Move(offset);
  if (item_view_)
	item_view_->Move(offset);
}

void ItemSlot::SetPosition(const sf::Vector2f &new_position) {
  Window::SetPosition(new_position);
  if (item_view_)
	item_view_->SetPosition(new_position + item_position_offset_);
}

bool ItemSlot::IsEmpty() const { return item_view_ == nullptr; }

void ItemSlot::Deserialize(const boost::property_tree::ptree &ptree) {
  Window::Deserialize(ptree);
}

void ItemSlot::Update(float delta_time) {
  Window::Update(delta_time);
  if (!item_view_) return;
  item_view_->Update(delta_time);

  if (!parent_) return;
  const sf::FloatRect
	  kClickArea{Window::GetRectangleShape().getPosition().x, Window::GetRectangleShape().getPosition().y,
				 Window::GetRectangleShape().getSize().x, Window::GetRectangleShape().getSize().y};
  if (InputManager::IsMouseButtonClickedOn(sf::Mouse::Left, kClickArea)) {
	parent_->OnChildrenWindowEvent(this, WindowEvent::kLeftMouseClick);
  }

}

void ItemSlot::Activate() {
  Window::Activate();
}

void ItemSlot::Deactivate() {
  Window::Deactivate();
}

void ItemSlot::RestoreDefault() {
  Window::RestoreDefault();
}

void ItemSlot::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  Window::draw(target, states);
  if (!Window::IsVisible()) return;

  if (item_view_)
	target.draw(*item_view_, states);
}





