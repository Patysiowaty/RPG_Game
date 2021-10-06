#include "Label.hpp"

Label::Label(const std::string &text, const sf::Color &text_color, const std::string &font_path) {
  font_.loadFromFile(font_path);
  rendered_text_.setFont(font_);
  rendered_text_.setCharacterSize(18);
  rendered_text_.setString(text);
  rendered_text_.setFillColor(text_color);
  rendered_text_.setOutlineThickness(0.4f);
  rendered_text_.setOutlineColor({123, 123, 123, 255});
}

Label::Label(const sf::Color &text_color, const std::string &font_path) {
  font_.loadFromFile(font_path);
  rendered_text_.setFont(font_);
  rendered_text_.setCharacterSize(18);
  rendered_text_.setFillColor(text_color);
  rendered_text_.setOutlineThickness(0.4f);
  rendered_text_.setOutlineColor({123, 123, 123, 255});
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
  Window::CenterTextToFit(rendered_text_, Window::GetRectangleShape());
}

void Label::SetPosition(const sf::Vector2f &new_position) {
  Window::SetPosition(new_position);
  rendered_text_.setPosition(new_position);
  Window::CenterTextToFit(rendered_text_, Window::GetRectangleShape());
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
}

void Label::SetTextOutlineColor(const sf::Color &color) {
  rendered_text_.setOutlineColor(color);
}

void Label::SetTextOutlineThickness(float size) {
  rendered_text_.setOutlineThickness(size);
}

void Label::SetTextString(const std::string &text_string) {
  rendered_text_.setString(text_string);
  Window::CenterTextToFit(rendered_text_, Window::GetRectangleShape());
}

void Label::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  if (!Window::IsVisible()) return;

  Window::draw(target, states);
  if (rendered_text_.getString() != "")
	target.draw(rendered_text_, states);
}




