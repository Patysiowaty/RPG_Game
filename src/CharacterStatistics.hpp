#ifndef CHARACTERSTATISTICS_HPP
#define CHARACTERSTATISTICS_HPP

#include <memory>
#include <vector>

#include "Statistic.hpp"
class CharacterStatistics {
 public:
  CharacterStatistics();

  std::shared_ptr<Statistic> GetStatistic(StatisticType statistic_type) const;

 private:
  std::vector<std::shared_ptr<Statistic>> statistic_;
};

#endif //CHARACTERSTATISTICS_HPP
