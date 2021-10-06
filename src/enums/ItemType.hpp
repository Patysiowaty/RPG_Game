#ifndef ITEMTYPE_HPP
#define ITEMTYPE_HPP
#include <cstdint>

enum class ItemType : std::int16_t {
  kNone = -1,
  kHelmet,
  kRing,
  kNecklace,
  kGloves,
  kOneHandedSword,
  kArmor,
  kPants,
  kBoots,
  kConsumptive,

  kSize = 9,
};

#endif //ITEMTYPE_HPP
