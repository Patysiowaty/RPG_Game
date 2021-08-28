#ifndef IUIELEMENT_HPP
#define IUIELEMENT_HPP

class IUIElement {
 public:
  virtual ~IUIElement() = default;
  virtual void Render(sf::RenderWindow &render_target) = 0;
  virtual void Update(const float &delta_time) = 0;
  virtual void SetPosition(const sf::Vector2f &position) = 0;
};

#endif //IUIELEMENT_HPP
