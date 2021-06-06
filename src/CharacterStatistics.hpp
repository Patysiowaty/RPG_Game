#ifndef CHARACTERSTATISTICS_HPP
#define CHARACTERSTATISTICS_HPP

#include <cstdint>

class CharacterStatistics {
 public:
  explicit CharacterStatistics();
  ~CharacterStatistics();

  void SetAttack(std::int32_t value);
  void AddAttack(std::int32_t value);
  void SubtractAttack(std::int32_t value);
  void RecalculateAttack(std::int32_t value);
  std::int32_t GetAttack() const { return attack_; }

  void SetHealth(std::int32_t value);
  void RecoverHealth(std::int32_t value);
  void SubtractHealth(std::int32_t value);
  std::int32_t GetCurrentHealth() const { return health_; }

  void SetMaxHealth(std::int32_t value);
  void IncreaseMaxHealth(std::int32_t value);
  void DecreaseMaxHealth(std::int32_t value);
  void RecalculateMaxHealth(std::int32_t value);
  std::int32_t GetMaxHealth() const { return max_health_; }

  void SetStamina(std::int32_t value);
  void RecoverStamina(std::int32_t value);
  void SubtractStamina(std::int32_t value);
  std::int32_t GetCurrentStamina() const { return stamina_; }

  void SetMaxStamina(std::int32_t value);
  void IncreaseMaxStamina(std::int32_t value);
  void DecreaseMaxStamina(std::int32_t value);
  void RecalculateMaxStamina(std::int32_t value);
  std::int32_t GetMaxStamina() const { return max_stamina_; }

  void SetMana(std::int32_t value);
  void RecoverMana(std::int32_t value);
  void SubtractMana(std::int32_t value);
  std::int32_t GetMana() const { return mana_; }

  void SetMaxMana(std::int32_t value);
  void IncreaseMaxMana(std::int32_t value);
  void DecreaseMaxMana(std::int32_t value);
  void RecalculateMaxMana(std::int32_t value);
  std::int32_t GetMaxMana() const { return max_mana_; }

  void SetArmor(std::int32_t value);
  void AddArmor(std::int32_t value);
  void SubtractArmor(std::int32_t value);
  std::int32_t GetArmor() const { return armor_; }

  void SetMaxArmor(std::int32_t value);
  void IncreaseMaxArmor(std::int32_t value);
  void DecreaseMaxArmor(std::int32_t value);
  std::int32_t GetMaxArmor() const { return max_armor_; }



 private:
  static constexpr std::int32_t kMaxStatValue = 999999;

  std::int32_t attack_{0};
  std::int32_t health_{0};
  std::int32_t max_health_{0};
  std::int32_t stamina_{0};
  std::int32_t max_stamina_{0};
  std::int32_t mana_{0};
  std::int32_t max_mana_{0};
  std::int32_t armor_{0};
  std::int32_t max_armor_{0};
  std::int32_t evade_{0};
};

#endif //CHARACTERSTATISTICS_HPP
