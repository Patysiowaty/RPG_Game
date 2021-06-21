#ifndef PLAYERSTATISTICS_HPP
#define PLAYERSTATISTICS_HPP

#include <memory>
#include <vector>
#include "SingleStatistic.hpp"
#include "RangeStatistic.hpp"
#include "interfaces/IAttributesHandler.hpp"
#include "interfaces/ILevelHandler.hpp"
#include "interfaces/IItemHandler.hpp"

class PlayerStatistics : public IAttributesHandler, public ILevelHandler, public IItemHandler {
 public:
  PlayerStatistics();

  const std::unique_ptr<SingleStatistic> &GetSingleStatistic(StatisticType statistic_type) const;
  const std::unique_ptr<RangeStatistic> &GetRangeStatistic(StatisticType statistic_type) const;
  void AddSingleStatistic(StatisticType statistic_type, std::int32_t value = 0);
  void AddRangeStatistic(StatisticType statistic_type, std::int32_t value = 0);

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
  std::vector<std::unique_ptr<SingleStatistic>> single_statistics_;
  std::vector<std::unique_ptr<RangeStatistic>> range_statistics_;
  uint16_t player_level_{1};
};

#endif //PLAYERSTATISTICS_HPP
