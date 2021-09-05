#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Window.hpp"

Window::Window() {
}

void Window::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  if (!is_visible_) return;

  target.draw(shape_, states);
}

void Window::Deserialize(const boost::property_tree::ptree &ptree) {
  const auto &window_ptree = ptree.get_child("window");

  shape_.setSize({window_ptree.get<float>("size.width"), window_ptree.get<float>("size.height")});
  shape_.setPosition({window_ptree.get<float>("position.x"), window_ptree.get<float>("position.y")});
  shape_.setFillColor(CreateColor(window_ptree.get<std::string>("backgroundColor")));
  shape_.setOutlineColor(CreateColor(window_ptree.get<std::string>("outlineColor")));

  texture_.loadFromFile(window_ptree.get<std::string>("texturePath"));

  texture_rect_.left = window_ptree.get<int>("textureRect.left");
  texture_rect_.top = window_ptree.get<int>("textureRect.top");
  texture_rect_.width = window_ptree.get<int>("textureRect.width");
  texture_rect_.height = window_ptree.get<int>("textureRect.height");
  Window::SetWindowTexture(&texture_, texture_rect_);
}

void Window::Move(const sf::Vector2f &offset) {
  shape_.move(offset);
}

sf::Color Window::CreateColor(const std::string &color_data) {
  std::vector<std::string> colors;
  std::vector<std::uint8_t> int_colors_;
  int_colors_.reserve(colors.size());
  boost::split(colors, color_data, boost::is_any_of(";"));
  for (auto &color : colors) {
	int_colors_.push_back(std::stoi(color));
  }
  return sf::Color{int_colors_.at(0), int_colors_.at(1), int_colors_.at(2), int_colors_.at(3)};
}

void Window::Update(float delta_time) {

}

void Window::CenterTextToFit(sf::Text &text, const sf::Shape &shape) {
  const auto &global_rect_bounds = shape.getGlobalBounds();
  const auto &local_text_bounds = text.getLocalBounds();
  const auto centered_text = sf::Vector2f((global_rect_bounds.width - local_text_bounds.width) / 2,
										  (global_rect_bounds.height - local_text_bounds.height) / 2);
  const auto
	  text_position = sf::Vector2f(static_cast<int>(centered_text.x + global_rect_bounds.left - local_text_bounds.left),
								   static_cast<int>(centered_text.y + global_rect_bounds.top - local_text_bounds.top));
  text.setPosition(text_position);
}

void Window::SetWindowTexture(sf::Texture *texture, const sf::IntRect &texture_pos) {
  shape_.setTexture(texture);
  shape_.setTextureRect(texture_pos);
  const sf::Vector2f size{static_cast<float>(texture_pos.width), static_cast<float>(texture_pos.height)};
  Window::SetSize(size);
}

void Window::SetPosition(const sf::Vector2f &new_position) {
  shape_.setPosition(new_position);
}

void Window::SetSize(const sf::Vector2f &new_size) {
  shape_.setSize(new_size);
}

void Window::Activate() {
  is_active_ = true;
  shape_.setFillColor(sf::Color::White);
}

void Window::Deactivate() {
  is_active_ = false;
  shape_.setFillColor({0, 0, 0, 60});
}

void Window::RestoreDefault() {
  is_active_ = true;
  Window::SetWindowTexture(&texture_, texture_rect_);
}

void Window::LoadWindowTexture(const std::string &file_path, const sf::IntRect &texture_pos) {
  texture_.loadFromFile(file_path, texture_pos);
  texture_rect_ = {0, 0, static_cast<int>(texture_.getSize().x), static_cast<int>(texture_.getSize().y)};
  Window::SetWindowTexture(&texture_, texture_rect_);
}






