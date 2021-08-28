#include "Button.hpp"
#include "../managers/InputManager.hpp"
Button::Button() {
  auto &shape = Window::GetRectangleShape();
  shape.setTexture(&base_texture_);
}

void Button::CenterTextToFit() {
  const auto &global_rect_bounds = Window::GetRectangleShape().getGlobalBounds();
  const auto &local_text_bounds = Window::GetText().getLocalBounds();
  const auto centered_text = sf::Vector2f((global_rect_bounds.width - local_text_bounds.width) / 2,
										  (global_rect_bounds.height - local_text_bounds.height) / 2);
  const auto
	  text_position = sf::Vector2f(static_cast<int>(centered_text.x + global_rect_bounds.left - local_text_bounds.left),
								   static_cast<int>(centered_text.y + global_rect_bounds.top - local_text_bounds.top));
  Window::GetText().setPosition(text_position);
}

void Button::AddCommand(CommandInvoker command_invoker, std::unique_ptr<ICommand> command) {
  commands_list_.emplace(command_invoker, std::move(command));
}

void Button::OnLeftMouseButtonClick() {
  if (commands_list_.find(CommandInvoker::kLeftMouseButtonClick) != commands_list_.end())
	commands_list_.at(CommandInvoker::kLeftMouseButtonClick)->Execute();
}

void Button::OnRightMouseButtonClick() {
  if (commands_list_.find(CommandInvoker::kRightMouseButtonClick) != commands_list_.end())
	commands_list_.at(CommandInvoker::kRightMouseButtonClick)->Execute();
}

void Button::OnMouseEnter() {
  if (is_focused_) return;

  is_focused_ = true;
  const auto hover_rect = sf::IntRect{sprite_rect.left + hover_offset_.x, sprite_rect.top + hover_offset_.y,
									  sprite_rect.width, sprite_rect.height};
  Window::GetRectangleShape().setTextureRect(hover_rect);
}

void Button::OnMouseLeave() {
  if (!is_focused_) return;

  is_focused_ = false;
  Window::GetRectangleShape().setTextureRect(sprite_rect);
}

void Button::Update(float delta_time) {
  Window::Update(delta_time);

  const auto &position = Window::GetRectangleShape();

  if (InputManager::IsMouseButtonClickedOn(sf::Mouse::Left, position.getGlobalBounds()))
	OnLeftMouseButtonClick();
  else if (InputManager::IsMouseButtonClickedOn(sf::Mouse::Right, position.getGlobalBounds()))
	OnRightMouseButtonClick();

  if (InputManager::IsMouseOver(position.getGlobalBounds()))
	OnMouseEnter();
  else if (!InputManager::IsMouseOver(position.getGlobalBounds()))
	OnMouseLeave();
}

void Button::Deserialize(const boost::property_tree::ptree &ptree) {
  Window::Deserialize(ptree);

  base_texture_.loadFromFile(ptree.get<std::string>("texturePath"));

  sprite_rect.left = ptree.get<int>("spriteSize.left");
  sprite_rect.top = ptree.get<int>("spriteSize.top");
  sprite_rect.width = ptree.get<int>("size.width");
  sprite_rect.height = ptree.get<int>("size.height");

  hover_offset_.x = ptree.get<int>("hoverOffset.x");
  hover_offset_.y = ptree.get<int>("hoverOffset.y");

  auto &shape = Window::GetRectangleShape();
  shape.setTextureRect(sprite_rect);
  base_texture_.setSmooth(true);

  auto &text = Window::GetText();
  text.setString(ptree.get<std::string>("text"));
  CenterTextToFit();
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  Window::draw(target, states);
}

void Button::SetPosition(const sf::Vector2f &position, bool use_relative) {
  auto &shape = Window::GetRectangleShape();
  if (use_relative) {
	const auto pos_x = (position.x - shape.getSize().x) / relative_position_.x;
	const auto pos_y = (position.y - shape.getSize().y) / relative_position_.y;
	shape.setPosition(pos_x, pos_y);
  } else {
	shape.setPosition(position);
  }
  CenterTextToFit();
}

void Button::Move(const sf::Vector2f &offset) {
  Window::Move(offset);
  CenterTextToFit();
}



