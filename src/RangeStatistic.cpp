#include "RangeStatistic.hpp"

RangeStatistic::RangeStatistic(StatisticType statistic_type, std::int32_t value, std::int32_t max_value)
	: SingleStatistic{statistic_type, value} {
  RangeStatistic::SetMaxValue(value);
  RangeStatistic::SetValue(value);
}

void RangeStatistic::SetValue(int32_t value) {
  return value > max_value_ ? Statistic::SetValue(max_value_) : value < 0 ? Statistic::SetValue(0) :
																Statistic::SetValue(value);
}

void RangeStatistic::SetMaxValue(int32_t value) {
  const auto kMaxValue = Statistic::GetMaxStatisticValue();
  max_value_ = value > kMaxValue ? kMaxValue : value;

  if (max_value_ < Statistic::GetValue())
	return Statistic::SetValue(max_value_);
}

void RangeStatistic::AddValue(int32_t value) {
  if (value < 0) return SubtractValue(-value);

  const auto kMaxValue = Statistic::GetMaxStatisticValue();
  const auto kValue = Statistic::GetValue();

  return (kValue + value) > max_value_ ? Statistic::SetValue(max_value_) : SingleStatistic::AddValue(value);
}

void RangeStatistic::AddMaxValue(int32_t value) {
  if (value < 0) return SubtractMaxValue(-value);

  const auto kMaxValue = Statistic::GetMaxStatisticValue();

  max_value_ = (max_value_ + value) > kMaxValue ? kMaxValue : max_value_ + value;
}

void RangeStatistic::SubtractMaxValue(int32_t value) {
  if (value < 0) return AddMaxValue(-value);

  max_value_ = (max_value_ - value) < 0 ? 0 : max_value_ - value;

  if (max_value_ < Statistic::GetValue())
	return Statistic::SetValue(max_value_);
}

int32_t RangeStatistic::GetMaxValue() const {
  return max_value_;
}

double RangeStatistic::GetPercentageValue() const {
  return static_cast<double>(Statistic::GetValue()) / max_value_;
}


