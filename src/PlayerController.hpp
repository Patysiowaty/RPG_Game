#ifndef PLAYERCONTROLLER_HPP
#define PLAYERCONTROLLER_HPP

#include "Player.hpp"

class PlayerController {
 public:
  PlayerController(Player &player);

 private:
  Player &player_;
};

#endif //PLAYERCONTROLLER_HPP
