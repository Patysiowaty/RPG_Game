#ifndef ISTATISTIC_HPP
#define ISTATISTIC_HPP

#include "../enums/StatisticType.hpp"
#include <cstdint>
class IStatistic {
 public:
  virtual StatisticType GetType() const = 0;
  virtual void SetValue(std::int32_t value) = 0;
  virtual std::int32_t GetValue() const = 0;
  virtual double GetPercentageValue() const = 0;
};

#endif //ISTATISTIC_HPP
