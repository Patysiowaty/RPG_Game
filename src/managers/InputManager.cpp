#include "InputManager.hpp"

std::map<sf::Keyboard::Key, InputState> InputManager::keys_states_list_;
std::map<sf::Mouse::Button, InputState> InputManager::mouse_states_list_;
sf::Event::MouseMoveEvent InputManager::last_mouse_position_;
sf::Event::MouseMoveEvent InputManager::mouse_position_;
std::unique_ptr<char> InputManager::provided_char_;

InputManager::InputManager() {
  for (int i = 0; i < sf::Keyboard::Key::KeyCount; ++i) {
	keys_states_list_.emplace(sf::Keyboard::Key(i), InputState::kNone);
  }

  for (int i = 0; i < sf::Mouse::Button::ButtonCount; ++i) {
	mouse_states_list_.emplace(sf::Mouse::Button(i), InputState::kNone);
  }
}

bool InputManager::IsKeyPressed(sf::Keyboard::Key key_code) {
  return keys_states_list_.at(key_code) == InputState::kPressed;
}

bool InputManager::IsKeyReleased(sf::Keyboard::Key key_code) {
  return keys_states_list_.at(key_code) == InputState::kReleased;
}

bool InputManager::IsMouseButtonPressed(sf::Mouse::Button button_code) {
  return mouse_states_list_.at(button_code) == InputState::kPressed;
}

bool InputManager::IsMouseButtonReleased(sf::Mouse::Button button_code) {
  return mouse_states_list_.at(button_code) == InputState::kReleased;
}

bool InputManager::IsMouseOver(const sf::IntRect &area) {
  return area.contains(mouse_position_.x, mouse_position_.y);
}

bool InputManager::IsMouseOver(const sf::FloatRect &area) {
  return area.contains(static_cast<float>(mouse_position_.x), static_cast<float>(mouse_position_.y));
}

const std::unique_ptr<char> &InputManager::GetNextCharacter() {
  return provided_char_;
}

void InputManager::RegisterNextInput(const sf::Event &event) {
  Clear();
  switch (event.type) {
	case sf::Event::TextEntered: {
	  auto value = event.text.unicode;
	  if (value > 32 && value < 127)
		provided_char_ = std::make_unique<char>(value);
	  break;
	}
	case sf::Event::KeyPressed:
	  keys_states_list_.at(event.key.code) = InputState::kPressed;
	  break;
	case sf::Event::KeyReleased:
	  if (auto &key_state = keys_states_list_.at(event.key.code); key_state == InputState::kPressed)
		key_state = InputState::kReleased;
	  break;
	case sf::Event::MouseButtonPressed:
	  mouse_states_list_.at(event.mouseButton.button) = InputState::kPressed;
	  last_mouse_position_ = mouse_position_;
	  mouse_position_.x = event.mouseButton.x;
	  mouse_position_.y = event.mouseButton.y;
	  break;
	case sf::Event::MouseButtonReleased:
	  mouse_states_list_.at(event.mouseButton.button) = InputState::kReleased;
	  last_mouse_position_ = mouse_position_;
	  mouse_position_.x = event.mouseButton.x;
	  mouse_position_.y = event.mouseButton.y;
	  break;
	case sf::Event::MouseMoved:
	  last_mouse_position_ = mouse_position_;
	  mouse_position_ = event.mouseMove;
	  break;
	default:
	  break;
  }
}

void InputManager::Clear() {
  for (auto &[first, second]: keys_states_list_) {
	if (second == InputState::kReleased)
	  second = InputState::kNone;
  }

  for (auto&[first, second]: mouse_states_list_) {
	if (second == InputState::kReleased)
	  second = InputState::kNone;
  }

  provided_char_.reset(nullptr);
}

bool InputManager::IsMouseButtonClickedIn(sf::Mouse::Button button_code, const sf::Vector2i &position) {
  return IsMouseButtonReleased(button_code) && IsMousePoint(position);
}

bool InputManager::IsMouseButtonClickedOn(sf::Mouse::Button button_code, const sf::IntRect &area) {
  return IsMouseButtonReleased(button_code) && IsMouseOver(area);
}

bool InputManager::IsMousePoint(const sf::Vector2i &position) {
  return mouse_position_.x == position.x && mouse_position_.y == position.y;
}

bool InputManager::IsMouseButtonClickedIn(sf::Mouse::Button button_code, const sf::Vector2f &position) {
  return IsMouseButtonReleased(button_code) && IsMousePoint(position);
}

bool InputManager::IsMouseButtonClickedOn(sf::Mouse::Button button_code, const sf::FloatRect &area) {
  return IsMouseButtonReleased(button_code) && IsMouseOver(area);
}

bool InputManager::IsMousePoint(const sf::Vector2f &position) {
  return mouse_position_.x == static_cast<int>(position.x) && mouse_position_.y == static_cast<int>(position.y);
}


