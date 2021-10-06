#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "../interfaces/IuiElement.hpp"
#include "../interfaces/ICommand.hpp"
#include "../enums/CommandInvoker.hpp"
#include "Window.hpp"

class Button : public Window {
 public:
  explicit Button(Window *parent = nullptr);
  explicit Button(std::string text, Window *parent = nullptr);
  Button(Button &&button) noexcept;

  void AddCommand(CommandInvoker command_invoker, std::unique_ptr<ICommand> command);

  void Update(float delta_time) override;
  void Deserialize(const boost::property_tree::ptree &ptree) override;
  void SetPosition(const sf::Vector2f &position) override;
  void SetPosition(const sf::Vector2f &position, bool use_relative);
  void SetTextString(const std::string &text_string, const sf::Color &color = sf::Color::White,
					 std::uint32_t text_size = 30);
  void SetTextOutline(const sf::Color &color, float thickness = 1.f);
  void LoadButtonHover(const std::string &path, const sf::IntRect &hover_rect = sf::IntRect{});
  void LoadFont(const std::string &path);
  void Move(const sf::Vector2f &offset) override;
  void Activate() override;
  void Deactivate() override;
  void RestoreDefault() override;

 private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  void OnLeftMouseButtonClick();
  void OnRightMouseButtonClick();
  void OnMouseEnter();
  void OnMouseLeave();

 private:
  Window *parent_;
  sf::Texture hover_texture_;
  sf::IntRect hover_rect_ = sf::IntRect{};

  std::map<CommandInvoker, std::unique_ptr<ICommand>> commands_list_;
  std::string text_string_;
  sf::Vector2f relative_position_;
  sf::Font font_;
  sf::Text text_;

  bool is_focused_{false};
};

#endif //BUTTON_HPP
