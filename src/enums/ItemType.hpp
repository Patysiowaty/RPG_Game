#ifndef ITEMTYPE_HPP
#define ITEMTYPE_HPP
#include <cstdint>

enum class ItemType : uint16_t {
  kNone = 0,
  kHelmet,
  kRing,
  kNecklace,
  kGloves,
  kOneHandedSword,
  kArmor,
  kOffHand,
  kPants,
  kBoots,
  kConsumptive,

  kSize = 11,
};

#endif //ITEMTYPE_HPP
