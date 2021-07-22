#ifndef EVENTDISPATCHER_HPP
#define EVENTDISPATCHER_HPP

#include "interfaces/IPublisher.hpp"
#include "interfaces/IEventHandler.hpp"
#include <vector>
#include <SFML/Window/Event.hpp>
class EventDispatcher : public IPublisher<IEventHandler> {
 public:
  void RegisterHandler(IEventHandler *value) override;
  void DispatchEvent(const sf::Event &event);

 private:
  std::vector<IEventHandler *> handlers_list_;
};

#endif //EVENTDISPATCHER_HPP
