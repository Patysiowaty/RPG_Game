#include "EventDispatcher.hpp"
void EventDispatcher::RegisterHandler(IEventHandler *value) {
  handlers_list_.emplace_back(value);
}

void EventDispatcher::DispatchEvent(const sf::Event &event) {
  switch (event.type) {
	case sf::Event::KeyPressed:
	  for (auto handler: handlers_list_) {
		handler->OnKeyDown(event);
	  }
	  break;
	case sf::Event::KeyReleased:
	  for (auto handler: handlers_list_) {
		handler->OnKeyUp(event);
	  }
	  break;
	case sf::Event::MouseWheelScrolled:
	  break;
	case sf::Event::MouseButtonPressed:
	  for (auto handler: handlers_list_) {
		handler->OnMouseDown(event);
	  }
	  break;
	case sf::Event::MouseButtonReleased:
	  for (auto handler: handlers_list_) {
		handler->OnMouseUp(event);
	  }
	  break;
	case sf::Event::MouseMoved:
	  for (auto handler: handlers_list_) {
		handler->OnMouseMove(event);
	  }
	  break;
	default:
	  break;
  }
}
