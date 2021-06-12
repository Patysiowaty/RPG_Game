#ifndef CHARACTERCLASS_HPP
#define CHARACTERCLASS_HPP
#include <cstdint>

enum class CharacterClass : std::uint16_t {
  kNone = 0,
  kWarrior = 1 << 0,
  kMage = 1 << 1,
  kHunter = 1 << 2,
};

#endif //CHARACTERCLASS_HPP
