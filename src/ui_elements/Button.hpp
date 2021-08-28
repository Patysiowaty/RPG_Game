#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "../interfaces/IuiElement.hpp"
#include "../interfaces/ICommand.hpp"
#include "../enums/CommandInvoker.hpp"
#include "Window.hpp"

class Button : public Window {
 public:
  Button();

  void AddCommand(CommandInvoker command_invoker, std::unique_ptr<ICommand> command);

  void Update(float delta_time) override;
  void Deserialize(const boost::property_tree::ptree &ptree) override;
  void SetPosition(const sf::Vector2f &position, bool use_relative = false);
  void Move(const sf::Vector2f &offset) override;

 private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  void CenterTextToFit();
  void OnLeftMouseButtonClick();
  void OnRightMouseButtonClick();
  void OnMouseEnter();
  void OnMouseLeave();

 private:
  sf::Texture base_texture_;
  std::map<CommandInvoker, std::unique_ptr<ICommand>> commands_list_;
  sf::Vector2f relative_position_;
  sf::IntRect sprite_rect;
  sf::Vector2i hover_offset_;

  bool is_focused_{false};
};

#endif //BUTTON_HPP
