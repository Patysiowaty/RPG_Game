#ifndef CHARACTERSTATISTICS_HPP
#define CHARACTERSTATISTICS_HPP

#include <memory>
#include <vector>

#include "Statistic.hpp"
class CharacterStatistics {
 public:
  CharacterStatistics();

  std::shared_ptr<Statistic> GetStatistic(StatisticType statistic_type) const;
  void AddStatistic(StatisticType statistic_type, std::int32_t value = 0);
  void AddStatistic(std::shared_ptr<Statistic> statistic);

 private:
  std::vector<std::shared_ptr<Statistic>> statistics_;
};

#endif //CHARACTERSTATISTICS_HPP
