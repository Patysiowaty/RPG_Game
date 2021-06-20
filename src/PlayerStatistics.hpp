#ifndef PLAYERSTATISTICS_HPP
#define PLAYERSTATISTICS_HPP

#include <memory>
#include <vector>
#include "Statistic.hpp"
#include "interfaces/IAttributesHandler.hpp"
#include "interfaces/ILevelHandler.hpp"
#include "Attribute.hpp"
#include "interfaces/IItemHandler.hpp"

class PlayerStatistics : public IAttributesHandler, public ILevelHandler, public IItemHandler {
 public:
  PlayerStatistics();

  std::shared_ptr<Statistic> GetStatistic(StatisticType statistic_type) const;
  void AddStatistic(StatisticType statistic_type, std::int32_t value = 0);
  void AddStatistic(std::shared_ptr<Statistic> statistic);

  void OnAttributesUpdate(const std::vector<std::shared_ptr<Attribute>> &attributes) override;
  void OnAttributeUpdate(const std::shared_ptr<Attribute> &attribute) override;
  void OnEquipItem(const std::shared_ptr<Item> &item) override;
  void OnTakeOffItem(const std::shared_ptr<Item> &item) override;
  void OnUsedItem(const std::shared_ptr<Item> &item) override;
  void OnLevelRaise() override;
  void OnLevelDowngrade() override;
  void OnLevelUpdate(int value) override;

 private:
  void ReloadStatistics(const std::shared_ptr<Attribute> &attribute);

 private:
  std::vector<std::shared_ptr<Statistic>> statistics_;
  uint16_t player_level_{1};
};

#endif //PLAYERSTATISTICS_HPP
