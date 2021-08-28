#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "Window.hpp"
#include "../managers/WindowsManager.hpp"

Window::Window() {
  text_.setFont(font_);
}

void Window::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  if (!visible_) return;
  states.transform *= shape_.getTransform();
  target.draw(shape_);
  states.transform *= text_.getTransform();
  target.draw(text_);
}

void Window::Deserialize(const boost::property_tree::ptree &ptree) {
  name_ = ptree.get<std::string>("name");
  shape_.setSize({ptree.get<float>("size.width"), ptree.get<float>("size.height")});
  shape_.setPosition({ptree.get<float>("position.x"), ptree.get<float>("position.y")});
  font_.loadFromFile(ptree.get<std::string>("fontPath"));
  text_.setCharacterSize(ptree.get<std::uint32_t>("fontSize"));
  text_.setFillColor(CreateColor(ptree.get<std::string>("fontColor")));
  shape_.setFillColor(CreateColor(ptree.get<std::string>("backgroundColor")));
  shape_.setOutlineColor(CreateColor(ptree.get<std::string>("outlineColor")));
}

void Window::Move(const sf::Vector2f &offset) {
  shape_.move(offset);
  text_.move(offset);
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






