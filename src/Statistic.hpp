#ifndef STATISTIC_HPP
#define STATISTIC_HPP
#include "interfaces/IStatistic.hpp"
#include "interfaces/IBaseValueContainer.hpp"

class Statistic : public IStatistic, public IBaseValueContainer<std::int32_t> {
 public:
  explicit Statistic(StatisticType statistic_type, std::int32_t value = 0);

  virtual void SetValue(std::int32_t value) override;

  StatisticType GetType() const override;
  std::int32_t GetValue() const override;
  virtual double GetPercentageValue() const;
  std::int32_t GetMaxStatisticValue() const;

  bool operator==(const Statistic &rhs);
  bool operator!=(const Statistic &rhs);

 private:
  constexpr static std::int32_t kMaxStatisticValue{999999};
  StatisticType statistic_type_{StatisticType::kNone};
  std::int32_t statistic_value_{0};
};

#endif //STATISTIC_HPP
