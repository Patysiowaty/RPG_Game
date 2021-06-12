#ifndef STATISTIC_HPP
#define STATISTIC_HPP
#include "interfaces/IRangeValueContainer.hpp"
#include <cstdint>
#include "enums/StatisticType.hpp"

class Statistic : public IRangeValueContainer<std::int32_t> {
 public:
  explicit Statistic(StatisticType statistic_type, std::int32_t max_value = 0, std::int32_t value = 0);

  void SetValue(std::int32_t value) override;
  void SetMaxValue(std::int32_t value) override;
  void AddValue(std::int32_t value) override;
  void AddMaxValue(std::int32_t value) override;
  void SubtractValue(std::int32_t value) override;
  void SubtractMaxValue(std::int32_t value) override;

  std::int32_t GetMaxValue() const override;
  virtual std::int32_t GetValue() const override;
  double GetPercent() const override;
  StatisticType GetType() const;

  bool operator==(const Statistic &rhs);
  bool operator!=(const Statistic &rhs);

 private:
  constexpr static std::int32_t kMaxStatisticValue{999999};
  StatisticType statistic_type_;
  std::int32_t statistic_;
  std::int32_t max_statistic_;
};

#endif //STATISTIC_HPP
