#include "ItemSlot.hpp"
ItemSlot::ItemSlot() {

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

  if (item_view_)
	target.draw(*item_view_, states);
}





