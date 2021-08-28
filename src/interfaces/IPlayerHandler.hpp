#ifndef IPLAYERHANDLER_HPP
#define IPLAYERHANDLER_HPP

class IPlayerHandler {
 public:
  virtual ~IPlayerHandler() = default;
  virtual void OnPlayerMove(const sf::Vector2<float> &offset) = 0;
};
#endif //IPLAYERHANDLER_HPP
