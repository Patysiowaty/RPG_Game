#ifndef COLLIDER_HPP
#define COLLIDER_HPP
#include <SFML/Graphics/RectangleShape.hpp>

class Collider : public sf::Drawable {
 public:
  Collider(sf::Color color = sf::Color::Red) {
	action_radius_.setOutlineColor(color);
	action_radius_.setOutlineThickness(1.f);
	action_radius_.setFillColor(sf::Color::Transparent);
  }

  void SetPosition(const sf::Vector2f &new_position) {
	action_radius_.setPosition(new_position);
  }

  void SetRadius(const sf::Vector2f &new_radius) {
	action_radius_.setSize(new_radius);
  }

  void SetVisible(bool visible) { visible_ = visible; }

 protected:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
	if (!visible_) return;
	states.transform *= action_radius_.getTransform();
  }

 private:
  sf::RectangleShape action_radius_;
  bool visible_{false};
};
#endif //COLLIDER_HPP
