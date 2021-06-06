#ifndef CHARACTERATTRIBUTES_HPP
#define CHARACTERATTRIBUTES_HPP

#include <cstdint>
#include <memory>
#include "IItemHandler.hpp"
#include "ILevelHandler.hpp"

class CharacterAttributes : public IItemHandler, public ILevelHandler {
 public:
  explicit CharacterAttributes();

  void OnEquipItem(const std::shared_ptr<Item> &item) override {}
  void OnLevelUpdate() override;
  void OnTakeOffItem(const std::shared_ptr<Item> &item) override {}
  void OnUsedItem(const std::shared_ptr<Item> &item) override {}

  int32_t GetStrength() const { return base_strength_ + strength_; }
  int32_t GetDexterity() const { return base_dexterity_ + dexterity_; }
  int32_t GetVitality() const { return base_vitality_ + vitality_; }
  int32_t GetIntelligence() const { return base_intelligence_ + intelligence_; }

  void SetBaseAttributes(int32_t strength, int32_t dexterity, int32_t vitality, int32_t intelligence);
  void SetAttributes(int32_t strength, int32_t dexterity, int32_t vitality, int32_t intelligence);
  void SetStrength(int32_t strength);
  void SetDexterity(int32_t dexterity);
  void SetVitality(int32_t vitality);
  void SetIntelligence(int32_t intelligence);

  void AddStrength(int32_t value);
  void AddDexterity(int32_t value);
  void AddVitality(int32_t value);
  void AddIntelligence(int32_t value);

  void SubtractStrength(int32_t value);
  void SubtractDexterity(int32_t value);
  void SubtractVitality(int32_t value);
  void SubtractIntelligence(int32_t value);

  void RaiseBaseAttributes();

 private:
  int32_t base_strength_{10};
  int32_t base_dexterity_{10};
  int32_t base_vitality_{10};
  int32_t base_intelligence_{10};

  int32_t strength_{0};
  int32_t dexterity_{0};
  int32_t vitality_{0};
  int32_t intelligence_{0};
};

#endif //CHARACTERATTRIBUTES_HPP
