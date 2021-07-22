#include "Button.hpp"
Button::Button() = default;

Button::Button(const std::string &text, const sf::Font &font, std::uint32_t character_size) : text_{text, font,
																									character_size} {

}

void Button::Update(const sf::Time &delta_time) {

}

void Button::Render(sf::RenderWindow &render_target) const {
  render_target.draw(sprite_);
  render_target.draw(text_);
}

void Button::SetPosition(const sf::Vector2f &position) {
  position_ = position;
  sprite_.setPosition(position_);
  CenterTextToFit();
}

void Button::CenterTextToFit() {
  const auto &global_sprite_bounds = sprite_.getGlobalBounds();
  const auto &local_text_bounds = text_.getLocalBounds();
  const auto centered_text = sf::Vector2f((global_sprite_bounds.width - local_text_bounds.width) / 2,
										  (global_sprite_bounds.height - local_text_bounds.height) / 2);
  const auto text_position =
	  sf::Vector2f(centered_text.x + global_sprite_bounds.left - local_text_bounds.left,
				   centered_text.y + global_sprite_bounds.top - local_text_bounds.top);
  text_.setPosition(text_position);
}

void Button::CreateSprite(const std::string &texture_path, const sf::IntRect &rect) {
  basic_texture_.loadFromFile(texture_path, rect);
  basic_texture_.setSmooth(true);
  sprite_.setTexture(basic_texture_);
  CenterTextToFit();
}

void Button::CreateText(const std::string &text, const sf::Font &font, std::uint32_t character_size, sf::Color color) {
  text_.setString(text);
  text_.setFont(font);
  text_.setCharacterSize(character_size);
  text_.setFillColor(color);
}

void Button::OnMouseMove(const sf::Event &event) {
  const auto kXPos = static_cast<float>(event.mouseButton.x);
  const auto kYPos = static_cast<float>(event.mouseButton.y);

  if (sprite_.getGlobalBounds().contains(kXPos, kYPos))
	OnMouseEnter();
  else
	OnMouseLeave();
}

void Button::OnMouseDown(const sf::Event &event) {
  const auto kXPos = static_cast<float>(event.mouseButton.x);
  const auto kYPos = static_cast<float>(event.mouseButton.y);
  const auto kWhichButton = event.mouseButton.button;

  if (sprite_.getGlobalBounds().contains(kXPos, kYPos)) {
	if (kWhichButton == sf::Mouse::Left) {
	  is_lmb_down_ = true;
	} else if (kWhichButton == sf::Mouse::Middle) {
	  is_mmb_down_ = true;
	} else if (kWhichButton == sf::Mouse::Right) {
	  is_rmb_down_ = true;
	}
  }
}

void Button::OnMouseUp(const sf::Event &event) {
  const auto kXPos = static_cast<float>(event.mouseButton.x);
  const auto kYPos = static_cast<float>(event.mouseButton.y);
  const auto kWhichButton = event.mouseButton.button;

  if (sprite_.getGlobalBounds().contains(kXPos, kYPos)) {
	if (kWhichButton == sf::Mouse::Left && is_lmb_down_) {
	  is_lmb_down_ = false;
	  OnLeftMouseButtonClick();
	} else if (kWhichButton == sf::Mouse::Middle && is_mmb_down_) {
	  is_mmb_down_ = false;
	} else if (kWhichButton == sf::Mouse::Right && is_rmb_down_) {
	  OnRightMouseButtonClick();
	  is_rmb_down_ = false;
	}
  }
}

void Button::OnKeyDown(const sf::Event &event) {

}

void Button::OnKeyUp(const sf::Event &event) {

}

void Button::OnMouseScroll(const sf::Event &event) {

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
}

void Button::OnMouseLeave() {
  if (!is_focused_) return;

  is_focused_ = false;
  is_lmb_down_ = false;
  is_mmb_down_ = false;
  is_rmb_down_ = false;
}


