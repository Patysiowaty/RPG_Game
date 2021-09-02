#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../interfaces/IjsonSerializable.hpp"
#include "../interfaces/IUpdatable.hpp"

class Window : public sf::Drawable, public IJSONDeserializable, public IUpdatable {
 public:
  Window();
  virtual ~Window() = default;

  virtual void Deserialize(const boost::property_tree::ptree &ptree);

  virtual void Update(float delta_time);
  virtual void Move(const sf::Vector2f &offset);
  virtual void SetPosition(const sf::Vector2f &new_position);
  virtual void Activate();
  virtual void Deactivate();
  virtual void RestoreDefault();
  virtual void SetSize(const sf::Vector2f &new_size);

  const std::string &GetWindowName() const { return name_; }

  void SetVisible(bool value) { visible_ = value; }

  bool IsVisible() const { return visible_; }
  sf::Font &GetFont()  { return font_; }
  sf::Text &GetText() { return text_; }
  sf::RectangleShape & GetRectangleShape()  { return shape_; }

 protected:
  sf::Color CreateColor(const std::string &color_data);
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

 private:
  sf::RectangleShape shape_;
  sf::Texture texture_;
  sf::IntRect texture_rect_;
  bool is_visible_{true};
  bool is_active_{true};
};

#endif //WINDOW_HPP
