#ifndef STATISTICTYPE_HPP
#define STATISTICTYPE_HPP

enum class StatisticType {
  kNone = -1,
  kAttack = 0,
  kMagicAttack = 1,
  kHealth = 2,
  kArmor = 3,
  kStamina = 4,
  kMana = 5,
  kMagicResistance = 6,
  kEvadeRatio = 7,
  kCriticalStrikeRatio = 8,
  kCriticalStrikeForce = 9,

  kSize = 10,
};

#endif //STATISTICTYPE_HPP
