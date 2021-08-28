#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP
#include <map>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <string>

enum class InputState {
  kNone, kPressed, kReleased
};

class InputManager {
 public:
  InputManager();

  void RegisterNextInput(const sf::Event &event);
  static bool IsKeyPressed(sf::Keyboard::Key key_code);
  static bool IsKeyReleased(sf::Keyboard::Key key_code);
  static bool IsMouseButtonPressed(sf::Mouse::Button button_code);
  static bool IsMouseButtonReleased(sf::Mouse::Button button_code);
  static bool IsMousePoint(const sf::Vector2i &position);
  static bool IsMousePoint(const sf::Vector2f &position);
  static bool IsMouseButtonClickedIn(sf::Mouse::Button button_code, const sf::Vector2i &position);
  static bool IsMouseButtonClickedIn(sf::Mouse::Button button_code, const sf::Vector2f &position);
  static bool IsMouseButtonClickedOn(sf::Mouse::Button button_code, const sf::IntRect &area);
  static bool IsMouseButtonClickedOn(sf::Mouse::Button button_code, const sf::FloatRect &area);
  static bool IsMouseOver(const sf::IntRect &area);
  static bool IsMouseOver(const sf::FloatRect &area);
  static const std::unique_ptr<char> &GetNextCharacter();

 private:
  void Clear();

 private:
  static std::unique_ptr<char> provided_char_;
  static std::map<sf::Keyboard::Key, InputState> keys_states_list_;
  static std::map<sf::Mouse::Button, InputState> mouse_states_list_;
  static sf::Event::MouseMoveEvent last_mouse_position_;
  static sf::Event::MouseMoveEvent mouse_position_;
};

#endif //INPUTMANAGER_HPP
