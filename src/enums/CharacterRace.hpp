#ifndef CHARACTERRACE_HPP
#define CHARACTERRACE_HPP

#include <cstdint>
enum class CharacterRace : uint16_t {
  kNone = 1 << 0,
  kHuman = 1 << 1,
};


#endif //CHARACTERRACE_HPP
