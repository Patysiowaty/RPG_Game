#ifndef SINGLESTATISTIC_HPP
#define SINGLESTATISTIC_HPP
#include "Statistic.hpp"
#include "interfaces/ISingleArithmeticValue.hpp"

class SingleStatistic : public Statistic, public ISingleArithmeticValue<std::int32_t> {
 public:
  explicit SingleStatistic(StatisticType statistic_type, std::int32_t value = 0);

  virtual void AddValue(std::int32_t value) override;
  void SubtractValue(std::int32_t value) override;

  SingleStatistic &operator+=(const Statistic &rhs);
  SingleStatistic &operator-=(const Statistic &rhs);
};

#endif //SINGLESTATISTIC_HPP
