#ifndef LABEL_HPP
#define LABEL_HPP

#include "Window.hpp"

enum class TextAlign {
  kNone,
  kLeft,
  kCenter,
  kRight
};

class Label : public Window {
 public:
  explicit Label(const std::string &text, const sf::Color &text_color = sf::Color::Black,
				 const std::string &font_path = "../resources/fonts/romulus.ttf");

  explicit Label(const sf::Color &text_color = sf::Color::Black,
				 const std::string &font_path = "../resources/fonts/romulus.ttf");

  Label(Label &&label) noexcept;

  void Update(float delta_time) override;
  void Move(const sf::Vector2f &offset) override;
  void Activate() override;
  void Deactivate() override;
  void RestoreDefault() override;

  void SetPosition(const sf::Vector2f &new_position) override;
  void SetTextColor(const sf::Color &color);
  void SetTextSize(std::uint16_t size);
  void SetTextOutlineColor(const sf::Color &color);
  void SetTextOutlineThickness(float size);
  void SetTextString(const std::string &text_string);
  void SetSize(const sf::Vector2f &size) override;
  void SetMarginLeft(float value);

  void SetAlign(TextAlign value);
  void LoadWindowTexture(const std::string &file_path, const sf::IntRect &texture_pos) override;

 protected:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void AlignText(TextAlign value);
  void AlignToLeft();
  void AlignToRight();
  void FitWindowSize();

 private:
  sf::Font font_;
  sf::Text rendered_text_;
  float margin_left_{3.f};
  TextAlign align_{TextAlign::kLeft};
};

#endif //LABEL_HPP
