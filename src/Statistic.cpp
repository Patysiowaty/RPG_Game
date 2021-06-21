#include "Statistic.hpp"

Statistic::Statistic(StatisticType statistic_type, std::int32_t value) : statistic_type_{statistic_type} {
  Statistic::SetValue(value);
}

StatisticType Statistic::GetType() const {
  return statistic_type_;
}

std::int32_t Statistic::GetValue() const {
  return statistic_value_;
}

void Statistic::SetValue(std::int32_t value) {
  statistic_value_ = value > kMaxStatisticValue ? kMaxStatisticValue : value;
}

double Statistic::GetPercentageValue() const {
  return 1.0;
}

std::int32_t Statistic::GetMaxStatisticValue() const {
  return kMaxStatisticValue;
}

bool Statistic::operator==(const Statistic &rhs) {
  return statistic_type_ == rhs.GetType();
}

bool Statistic::operator!=(const Statistic &rhs) {
  return !(*this == rhs);
}


