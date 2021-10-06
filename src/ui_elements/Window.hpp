#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../interfaces/IjsonSerializable.hpp"
#include "../interfaces/IUpdatable.hpp"
#include "../enums/WindowEvent.hpp"
#include <SFML/Graphics/Text.hpp>

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
  virtual void SetFillColor(sf::Color color) { shape_.setFillColor(color); }
  virtual void SetOutlineColor(sf::Color color) { shape_.setOutlineColor(color); }
  virtual void SetOutlineThickness(float value) { shape_.setOutlineThickness(value); }

  void SetColor(const sf::Color &color) { shape_.setFillColor(color); }
  void SetVisible(bool value) { is_visible_ = value; }
  void SetWindowTexture(sf::Texture *texture, const sf::IntRect &texture_pos = sf::IntRect{});
  void LoadWindowTexture(const std::string &file_path, const sf::IntRect &texture_pos = sf::IntRect{});
  void SetRelativePosition(const sf::Vector2f &new_position);

  bool IsVisible() const { return is_visible_; }
  bool IsActive() const { return is_active_; }
  const sf::RectangleShape &GetRectangleShape() const { return shape_; }

  virtual void OnChildrenWindowEvent(Window *sender, WindowEvent event_type) {}

 protected:
  sf::Color CreateColor(const std::string &color_data);
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  void CenterTextToFit(sf::Text &text, const sf::Shape &shape);

 private:
  sf::RectangleShape shape_;
  sf::Texture texture_;
  sf::IntRect texture_rect_;
  bool is_visible_{true};
  bool is_active_{true};
  sf::Vector2f relative_position_{.0f, .0f};
};

#endif //WINDOW_HPP
