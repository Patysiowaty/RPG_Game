#ifndef PLAYERCONTROLLER_HPP
#define PLAYERCONTROLLER_HPP

#include "../models/Player.hpp"
#include "../views/PlayerView.hpp"
#include "../interfaces/IPlayerHandler.hpp"
#include "../enums/Direction.hpp"
#include "../interfaces/IUpdatable.hpp"

class PlayerController : public IPublisher<IPlayerHandler>, public IUpdatable {
 public:
  PlayerController(Player &player, PlayerView &player_view);
  void Update(float delta_time) override;
  void RegisterHandler(IPlayerHandler *value) override;
  Player &GetPlayer() { return player_; }

  void MovePlayer(const sf::Vector2f &velocity, Direction direction);

 private:
  void MovePlayerDown(const sf::Vector2f &offset);
  void MovePlayerUp(const sf::Vector2f &offset);
  void MovePlayerLeft(const sf::Vector2f &offset);
  void MovePlayerRight(const sf::Vector2f &offset);

 private:
  const sf::Vector2f kMoveVelocityList[4] = {{0, 32.f}, {0.f, -32.f}, {-32.f, 0}, {32.f, 0}};
  Player &player_;
  PlayerView &player_view_;
  const float acceleration_ = 4.f;

  std::vector<IPlayerHandler *> handlers_;
};

#endif //PLAYERCONTROLLER_HPP
