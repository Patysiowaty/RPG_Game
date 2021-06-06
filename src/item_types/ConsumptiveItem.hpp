#ifndef CONSUMPTIVEITEM_HPP
#define CONSUMPTIVEITEM_HPP
#include "Item.hpp"
#include <memory>

class ConsumptiveItem : public Item {
 public:
  ConsumptiveItem();

  void SetHealthRegen(std::int32_t value);
  int32_t GetHealthRegen() const;

  void SetManaRegen(std::int32_t value);
  int32_t GetManaRegen() const;

  void SetStaminaRegen(std::int32_t value);
  std::int32_t GetStaminaRegen() const;

  void SetAdditionalHealthMax(std::int32_t value);
  std::int32_t GetAdditionalHealthMax() const;

  void SetAdditionalStamina(std::int32_t value);
  std::int32_t GetAdditionalStamina() const;

  void SetAdditionalMana(std::int32_t value);
  std::int32_t GetAdditionalMana() const;

 private:
  std::unique_ptr<std::int32_t> health_regen_;
  std::unique_ptr<std::int32_t> mana_regen_;
  std::unique_ptr<std::int32_t> stamina_regen_;
  std::unique_ptr<std::int32_t> additional_health_max_;
  std::unique_ptr<std::int32_t> additional_mana_;
  std::unique_ptr<std::int32_t> additional_stamina_;
};

#endif //CONSUMPTIVEITEM_HPP
