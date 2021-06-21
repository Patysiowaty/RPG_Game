#ifndef ICONSUMABLE_HPP
#define ICONSUMABLE_HPP

#include "../enums/StatisticType.hpp"
#include "../enums/AttributeType.hpp"

class ConsumptionEffect {
 public:

  void SetAttributesEffect(const std::vector<Attribute> &attributes);
  void SetStatisticEffect(const std::vector<> &statistics);

  const std::vector<std::pair<AttributeType, std::int32_t>> &GetAttributesEffect() const { return attributes_list_; }
  const std::vector<std::pair<StatisticType, std::int32_t>> &GetStatisticsEffect() const { return statistics_list_; }

 private:
  std::vector<std::pair<AttributeType, std::int32_t>> attributes_list_;
  std::vector<std::pair<StatisticType, std::int32_t >> statistics_list_;
};

class IConsumable {
 public:
  virtual ConsumptionEffect GetAfterConsumptionEffect() = 0;
};

#endif //ICONSUMABLE_HPP
