#include "SingleStatistic.hpp"
SingleStatistic::SingleStatistic(StatisticType statistic_type, std::int32_t value) : Statistic{statistic_type, value} {
}

void SingleStatistic::AddValue(std::int32_t value) {
  if (value < 0) return SubtractValue(-value);

  const auto statistic = Statistic::GetValue();
  const auto max_value = Statistic::GetMaxStatisticValue();

  return (value + statistic) > max_value ? Statistic::SetValue(max_value) : Statistic::SetValue(statistic + value);
}

void SingleStatistic::SubtractValue(std::int32_t value) {
  if (value < 0) return AddValue(-value);

  const auto statistic = Statistic::GetValue();
  const auto max_value = Statistic::GetMaxStatisticValue();

  return (statistic - value) < 0 ? Statistic::SetValue(0) : Statistic::SetValue(statistic - value);
}

SingleStatistic &SingleStatistic::operator+=(const Statistic &rhs) {
  AddValue(rhs.GetValue());
  return *this;
}

SingleStatistic &SingleStatistic::operator-=(const Statistic &rhs) {
  SubtractValue(rhs.GetValue());
  return *this;
}

