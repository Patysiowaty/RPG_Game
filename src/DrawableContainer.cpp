#include "DrawableContainer.hpp"
void DrawableContainer::Draw(sf::RenderWindow &window) const {
  for (const auto&[index, drawable_list]: indexed_drawable_list_) {
	for (const auto drawable: drawable_list) {
	  if (drawable == nullptr) continue;
	  window.draw(*drawable);
	}
  }
}

void DrawableContainer::AddDrawable(std::int32_t index, sf::Drawable *drawable) {
  if (const auto it = indexed_drawable_list_.find(index); it == indexed_drawable_list_.end())
	indexed_drawable_list_.emplace(index, std::list<sf::Drawable *>());

  auto &list_at_index = indexed_drawable_list_.at(index);
  list_at_index.emplace_back(drawable);
}
