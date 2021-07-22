#ifndef IFIGHTABLE_HPP
#define IFIGHTABLE_HPP

#include "../enums/BattleStates.hpp"
#include <cstdint>

class IFightable {
 public:
  virtual ~IFightable() = default;
  virtual std::int32_t Attack() const = 0;
  virtual void TakeDamage(std::int32_t value) = 0;
  virtual std::int32_t GetCurrentHealth() const = 0;
  virtual void SetBattleState(BattleStates battle_state) = 0;
  virtual bool IsAlive() const = 0;
  virtual std::uint16_t GetLevel() const = 0;

  virtual void AddExperience(std::size_t value) = 0;
};

#endif //IFIGHTABLE_HPP
