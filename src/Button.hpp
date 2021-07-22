#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include "interfaces/IuiElement.hpp"
#include "interfaces/ICommand.hpp"
#include "enums/CommandInvoker.hpp"
#include "interfaces/IEventHandler.hpp"

class Button : public IUIElement, public IEventHandler {
 public:
  Button();
  Button(const std::string &text, const sf::Font &font, std::uint32_t character_size);
  void SetPosition(const sf::Vector2f &position);
  void CreateSprite(const std::string &texture_path, const sf::IntRect &rect);
  void CreateText(const std::string &text, const sf::Font &font, std::uint32_t character_size,
				  sf::Color color = sf::Color::White);

  void AddCommand(CommandInvoker command_invoker, std::unique_ptr<ICommand> command);

  void Update(const sf::Time &delta_time);
  void Render(sf::RenderWindow &render_target) const;

  void OnMouseMove(const sf::Event &event) override;
  void OnMouseDown(const sf::Event &event) override;
  void OnMouseUp(const sf::Event &event) override;
  void OnKeyDown(const sf::Event &event) override;
  void OnKeyUp(const sf::Event &event) override;
  void OnMouseScroll(const sf::Event &event) override;

 protected:
  void OnLeftMouseButtonClick();
  void OnRightMouseButtonClick();
  void OnMouseEnter();
  void OnMouseLeave();

 private:
  void CenterTextToFit();

 private:
  sf::Text text_;
  sf::Sprite sprite_;
  sf::Texture basic_texture_;
  sf::Vector2f position_{.0f, .0f};

  std::map<CommandInvoker, std::unique_ptr<ICommand>> commands_list_;

  bool is_lmb_down_{false};
  bool is_rmb_down_{false};
  bool is_mmb_down_{false};

  bool is_focused_{false};
};

#endif //BUTTON_HPP
