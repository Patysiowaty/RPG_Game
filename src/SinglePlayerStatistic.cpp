#include "SinglePlayerStatistic.hpp"

SinglePlayerStatistic::SinglePlayerStatistic(StatisticType statistic_type, std::int32_t value, std::int32_t max_value)
	: statistic_type_{statistic_type} {
  SinglePlayerStatistic::SetMaxValue(max_value);
  SinglePlayerStatistic::SetValue(value);
}

void SinglePlayerStatistic::SetValue(int32_t value) {
  value_ = value > max_value_ ? max_value_ : value < 0 ? 0 : value;
}

void SinglePlayerStatistic::SetMaxValue(int32_t value) {
  max_value_ = value > kMaxValue ? kMaxValue : value;

  if (max_value_ < value_)
	return SinglePlayerStatistic::SetValue(max_value_);
}

void SinglePlayerStatistic::AddValue(int32_t value) {
  if (value < 0) return SubtractValue(-value);

  value_ = (value_ + value) > max_value_ ? max_value_ : value + value_;
}

void SinglePlayerStatistic::AddMaxValue(int32_t value) {
  if (value < 0) return SubtractMaxValue(-value);

  max_value_ = (max_value_ + value) > kMaxValue ? kMaxValue : max_value_ + value;
}

void SinglePlayerStatistic::SubtractValue(int32_t value) {
  if (value < 0) return AddValue(-value);

  value_ = (value_ - value) < 0 ? 0 : value_ - value;
}

void SinglePlayerStatistic::SubtractMaxValue(int32_t value) {
  if (value < 0) return AddMaxValue(-value);

  max_value_ = (max_value_ - value) < 0 ? 0 : max_value_ - value;

  if (max_value_ < value_)
	return SinglePlayerStatistic::SetValue(max_value_);
}

std::int32_t SinglePlayerStatistic::GetValue() const {
  return value_;
}

std::int32_t SinglePlayerStatistic::GetMaxValue() const {
  return max_value_;
}

double SinglePlayerStatistic::GetPercentageValue() const {
  return static_cast<double>(value_) / max_value_;
}

StatisticType SinglePlayerStatistic::GetType() const {
  return statistic_type_;
}




