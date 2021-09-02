#include "Button.hpp"
#include "../managers/InputManager.hpp"

Button::Button(Window *parent) : parent_{parent}, text_{text_string_, font_} {
}

Button::Button(std::string text, Window *parent) : parent_{parent}, text_string_{std::move(text)},
												   text_{text_string_, font_} {
  Window::CenterTextToFit(text_, Window::GetRectangleShape());
}

Button::Button(Button &&button) noexcept
	: parent_(button.parent_), commands_list_(std::move(button.commands_list_)), text_{text_string_, font_} {

}

void Button::AddCommand(CommandInvoker command_invoker, std::unique_ptr<ICommand> command) {
  commands_list_.emplace(command_invoker, std::move(command));
}

void Button::OnLeftMouseButtonClick() {
  if (commands_list_.find(CommandInvoker::kLeftMouseButtonClick) != commands_list_.end())
	commands_list_.at(CommandInvoker::kLeftMouseButtonClick)->Execute();
  if (parent_)
	parent_->OnChildrenWindowEvent(this, WindowEvent::kLeftMouseClick);
}

void Button::OnRightMouseButtonClick() {
  if (commands_list_.find(CommandInvoker::kRightMouseButtonClick) != commands_list_.end())
	commands_list_.at(CommandInvoker::kRightMouseButtonClick)->Execute();
  if (parent_)
	parent_->OnChildrenWindowEvent(this, WindowEvent::kRightMouseClick);
}

void Button::OnMouseEnter() {
  if (is_focused_) return;

  Activate();
  is_focused_ = true;

  if (parent_)
	parent_->OnChildrenWindowEvent(this, WindowEvent::kActivateWindow);
}

void Button::OnMouseLeave() {
  if (!is_focused_) return;

  RestoreDefault();
  is_focused_ = false;

  if (parent_)
	parent_->OnChildrenWindowEvent(this, WindowEvent::kRestoreDefault);
}

void Button::Update(float delta_time) {
  Window::Update(delta_time);
  if (!Window::IsActive()) return;

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
  const auto &button_ptree = ptree.get_child("button");

  font_.loadFromFile(button_ptree.get<std::string>("fontPath"));
  text_.setCharacterSize(button_ptree.get<std::uint32_t>("fontSize"));
  text_.setFillColor(CreateColor(button_ptree.get<std::string>("fontColor")));
  text_.setString(button_ptree.get<std::string>("text"));

  hover_texture_.loadFromFile(button_ptree.get<std::string>("hoverPath"));

  hover_rect_.left = button_ptree.get<int>("hoverRect.left");
  hover_rect_.top = button_ptree.get<int>("hoverRect.top");
  hover_rect_.width = button_ptree.get<int>("hoverRect.width");
  hover_rect_.height = button_ptree.get<int>("hoverRect.height");

  Window::CenterTextToFit(text_, Window::GetRectangleShape());
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  Window::draw(target, states);
  target.draw(text_);
}

void Button::SetPosition(const sf::Vector2f &position) {
  Window::SetPosition(position);
  Window::CenterTextToFit(text_, Window::GetRectangleShape());
}

void Button::SetPosition(const sf::Vector2f &position, bool use_relative) {
  if (use_relative) {
	const auto pos_x = (position.x - Window::GetRectangleShape().getSize().x) / relative_position_.x;
	const auto pos_y = (position.y - Window::GetRectangleShape().getSize().y) / relative_position_.y;
	Button::SetPosition(sf::Vector2f{pos_x, pos_y});
  } else
	Button::SetPosition(position);
}

void Button::Move(const sf::Vector2f &offset) {
  Window::Move(offset);
  text_.move(offset);

  Window::CenterTextToFit(text_, Window::GetRectangleShape());
}

void Button::Activate() {
  Window::Activate();
  if (hover_rect_ == sf::IntRect{}) return;

  Window::SetWindowTexture(&hover_texture_, hover_rect_);
}

void Button::Deactivate() {
  Window::Deactivate();
  text_.setFillColor({255, 255, 255, 64});
}

void Button::RestoreDefault() {
  Window::RestoreDefault();
  text_.setFillColor(sf::Color::White);
}

void Button::SetTextString(const std::string &text_string, const sf::Color &color, std::uint32_t text_size) {
  text_string_ = text_string;
  text_.setString(text_string_);
  text_.setFillColor(color);
  text_.setCharacterSize(text_size);
  Window::CenterTextToFit(text_, Window::GetRectangleShape());
}

void Button::LoadButtonHover(const std::string &path, const sf::IntRect &hover_rect) {
  hover_rect_ = hover_rect;
  hover_texture_.loadFromFile(path, hover_rect);
}

void Button::LoadFont(const std::string &path) {
  font_.loadFromFile(path);
}

void Button::SetTextOutline(const sf::Color &color, float thickness) {
  text_.setOutlineColor(color);
  text_.setOutlineThickness(thickness);
  Window::CenterTextToFit(text_, Window::GetRectangleShape());
}







