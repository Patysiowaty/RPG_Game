#ifndef LEVELMANAGER_HPP
#define LEVELMANAGER_HPP
#include <vector>
#include "CharacterLevel.hpp"
#include "PlayerExperience.hpp"
#include "ILevelHandler.hpp"
#include "enums/ErrorCodes/LevelManagerEC.hpp"

class LevelManager {
 public:
  explicit LevelManager(CharacterLevel *level);
  LevelManager(CharacterLevel *level, PlayerExperience *experience);
  void RegisterHandler(ILevelHandler *handler) { handlers_.push_back(handler); }

  LevelManagerEC AddExperience(std::int32_t value);
  LevelManagerEC IncreaseLevel(std::uint16_t value);

 private:
  CharacterLevel *level_;
  PlayerExperience *experience_;
  std::vector<ILevelHandler *> handlers_;
};

#endif //LEVELMANAGER_HPP
