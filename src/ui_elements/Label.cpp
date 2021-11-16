#include "Label.hpp"

Label::Label(const std::string &text, const sf::Color &text_color, const std::string &font_path) {
  font_.loadFromFile(font_path);
  rendered_text_.setFont(font_);
  rendered_text_.setCharacterSize(18);
  rendered_text_.setString(text);
  rendered_text_.setFillColor(text_color);
  Window::SetFillColor(sf::Color::Transparent);
}

Label::Label(const sf::Color &text_color, const std::string &font_path) {
  font_.loadFromFile(font_path);
  rendered_text_.setFont(font_);
  rendered_text_.setCharacterSize(18);
  rendered_text_.setFillColor(text_color);
  Window::SetFillColor(sf::Color::Transparent);
}

Label::Label(Label &&label) noexcept: font_{label.font_}, align_{label.align_} {
  rendered_text_.setFont(font_);
  rendered_text_.setString(label.rendered_text_.getString());
  rendered_text_.setCharacterSize(label.rendered_text_.getCharacterSize());
  rendered_text_.setFillColor(label.rendered_text_.getFillColor());
  rendered_text_.setOutlineThickness(label.rendered_text_.getOutlineThickness());
  rendered_text_.setOutlineColor(label.rendered_text_.getOutlineColor());
  rendered_text_.setPosition(label.rendered_text_.getPosition());
}

void Label::Update(float delta_time) {
  Window::Update(delta_time);
}

void Label::Move(const sf::Vector2f &offset) {
  Window::Move(offset);
  AlignText(align_);
}

void Label::SetPosition(const sf::Vector2f &new_position) {
  Window::SetPosition(new_position);
  rendered_text_.setPosition(new_position);
  AlignText(align_);
}

void Label::Activate() {
  Window::Activate();
}

void Label::Deactivate() {
  Window::Deactivate();
}

void Label::RestoreDefault() {
  Window::RestoreDefault();
}

void Label::SetTextColor(const sf::Color &color) {
  rendered_text_.setFillColor(color);
}

void Label::SetTextSize(std::uint16_t size) {
  rendered_text_.setCharacterSize(size);

  FitWindowSize();
}

void Label::SetTextOutlineColor(const sf::Color &color) {
  rendered_text_.setOutlineColor(color);
}

void Label::SetTextOutlineThickness(float size) {
  rendered_text_.setOutlineThickness(size);
}

void Label::SetTextString(const std::string &text_string) {
  rendered_text_.setString(text_string);
  AlignText(align_);

  FitWindowSize();
}

void Label::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  if (!Window::IsVisible()) return;

  Window::draw(target, states);
  if (!rendered_text_.getString().isEmpty())
	target.draw(rendered_text_, states);
}

void Label::SetAlign(TextAlign value) {
  align_ = value;

  AlignText(align_);
}

void Label::AlignToLeft() {
  const auto &kWndGlobalBounds = Window::GetRectangleShape().getGlobalBounds();
  const auto &kTextLocalBounds = rendered_text_.getLocalBounds();

  const auto kVerticalCenterPos = (kWndGlobalBounds.height - kTextLocalBounds.height) / 2;
  const auto kHorizontalPos = static_cast<int>(kWndGlobalBounds.left + margin_left_);

  const auto kTextPos = sf::Vector2f(kHorizontalPos, static_cast<int>(kVerticalCenterPos + kWndGlobalBounds.top
	  - kTextLocalBounds.top));

  rendered_text_.setPosition(kTextPos);
}

void Label::AlignToRight() {

  const auto &kWndGlobalBounds = Window::GetRectangleShape().getGlobalBounds();
  const auto &kTextLocalBounds = rendered_text_.getLocalBounds();

  const auto kVerticalCenterPos = (kWndGlobalBounds.height - kTextLocalBounds.height) / 2;
  const auto kHorizontalPos = kWndGlobalBounds.width - kTextLocalBounds.width + margin_left_;

  const auto kTextPos = sf::Vector2f(static_cast<int>(kHorizontalPos + kWndGlobalBounds.left - kTextLocalBounds.left),
									 static_cast<int>(kVerticalCenterPos + kWndGlobalBounds.top
										 - kTextLocalBounds.top));
  rendered_text_.setPosition(kTextPos);
}

void Label::AlignText(TextAlign value) {
  switch (value) {
	case TextAlign::kNone:
	  return;
	case TextAlign::kLeft:
	  return AlignToLeft();
	case TextAlign::kCenter:
	  return Window::CenterTextToFit(rendered_text_, Window::GetRectangleShape());
	case TextAlign::kRight:
	  return AlignToRight();
  }
}

void Label::FitWindowSize() {
  auto wnd_size = Window::GetRectangleShape().getSize();
  const auto &kTextBounds = rendered_text_.getLocalBounds();

  if (wnd_size.x < kTextBounds.width)
	wnd_size.x = kTextBounds.width;
  if (wnd_size.y < kTextBounds.height)
	wnd_size.y = kTextBounds.height;

  Window::SetSize(wnd_size);
}

void Label::SetSize(const sf::Vector2f &size) {
  auto current_size = Window::GetRectangleShape().getSize();

  if (current_size.x < size.x)
	current_size.x = size.x;
  if (current_size.y < size.y)
	current_size.y = size.y;

  Window::SetSize(current_size);
  AlignText(align_);
}

void Label::SetMarginLeft(float value) {
  margin_left_ = value;
  AlignText(align_);
}

void Label::LoadWindowTexture(const std::string &file_path, const sf::IntRect &texture_pos) {
  Window::LoadWindowTexture(file_path, texture_pos);
  SetFillColor(sf::Color::White);
}




