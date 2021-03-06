#ifndef CHARACTERSTATISTICSLIST_HPP
#define CHARACTERSTATISTICSLIST_HPP

#include <memory>
#include <vector>
#include "CharacterStatistic.hpp"
#include "../interfaces/IAttributesHandler.hpp"
#include "../interfaces/ILevelHandler.hpp"
#include "../interfaces/IItemHandler.hpp"

using StatisticsList = std::vector<std::unique_ptr<CharacterStatistic>>;
using StatisticPtr = std::unique_ptr<CharacterStatistic>;

class CharacterStatisticsList : public IAttributesHandler, public ILevelHandler, public IItemHandler {
 public:
  CharacterStatisticsList();

  const StatisticPtr &GetStatistic(StatisticType statistic_type) const;
  void AddNewStatistic(StatisticType statistic_type, std::int32_t max_value = 0, std::int32_t value = 0);

  void OnAttributesUpdate(const std::vector<std::unique_ptr<Attribute>> &attributes) override;
  void OnAttributeUpdate(const std::unique_ptr<Attribute> &attribute) override;
  void OnEquipItem(const std::shared_ptr<Item> &item) override;
  void OnTakeOffItem(const std::shared_ptr<Item> &item) override;
  void OnUsedItem(const std::shared_ptr<IConsumable> &item) override;
  void OnLevelRaise() override;
  void OnLevelDowngrade() override;
  void OnLevelUpdate(int value) override;

 private:
  void ReloadStatistics(const std::unique_ptr<Attribute> &attribute);

 private:
  StatisticsList statistic_list_;
  uint16_t player_level_{1};
};

#endif //CHARACTERSTATISTICSLIST_HPP
