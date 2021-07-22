#include "CharacterStatistic.hpp"

CharacterStatistic::CharacterStatistic(StatisticType statistic_type, std::int32_t value, std::int32_t max_value)
	: statistic_type_{statistic_type} {
  CharacterStatistic::SetMaxValue(max_value);
  CharacterStatistic::SetValue(value);
}

void CharacterStatistic::SetValue(int32_t value) {
  value_ = value > max_value_ ? max_value_ : value < 0 ? 0 : value;
}

void CharacterStatistic::SetMaxValue(int32_t value) {
  max_value_ = value > kMaxValue ? kMaxValue : value;

  if (max_value_ < value_)
	return CharacterStatistic::SetValue(max_value_);
}

void CharacterStatistic::AddValue(int32_t value) {
  if (value < 0) return SubtractValue(-value);

  value_ = (value_ + value) > max_value_ ? max_value_ : value + value_;
}

void CharacterStatistic::AddMaxValue(int32_t value) {
  if (value < 0) return SubtractMaxValue(-value);

  max_value_ = (max_value_ + value) > kMaxValue ? kMaxValue : max_value_ + value;
}

void CharacterStatistic::SubtractValue(int32_t value) {
  if (value < 0) return AddValue(-value);

  value_ = (value_ - value) < 0 ? 0 : value_ - value;
}

void CharacterStatistic::SubtractMaxValue(int32_t value) {
  if (value < 0) return AddMaxValue(-value);

  max_value_ = (max_value_ - value) < 0 ? 0 : max_value_ - value;

  if (max_value_ < value_)
	return CharacterStatistic::SetValue(max_value_);
}

std::int32_t CharacterStatistic::GetValue() const {
  return value_;
}

std::int32_t CharacterStatistic::GetMaxValue() const {
  return max_value_;
}

double CharacterStatistic::GetPercentageValue() const {
  return static_cast<double>(value_) / max_value_;
}

StatisticType CharacterStatistic::GetType() const {
  return statistic_type_;
}




