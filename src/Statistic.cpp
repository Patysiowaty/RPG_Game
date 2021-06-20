#include "Statistic.hpp"
Statistic::Statistic(StatisticType statistic_type, std::int32_t max_value, std::int32_t value) : statistic_type_{
	statistic_type}, max_statistic_{max_value}, statistic_{value} {

}

void Statistic::SetValue(std::int32_t value) {
  statistic_ = value > 0 ? value > kMaxStatisticValue ? kMaxStatisticValue : value : statistic_;
}

void Statistic::SetMaxValue(std::int32_t value) {
  max_statistic_ = value > 0 ? value > kMaxStatisticValue ? kMaxStatisticValue : value : max_statistic_;
  SetValue(value);
}

void Statistic::AddValue(std::int32_t value) {
  if (value < 0) return SubtractValue(-value);

  statistic_ = (statistic_ + value) > max_statistic_ ? max_statistic_ : statistic_ + value;
}

void Statistic::AddMaxValue(std::int32_t value) {
  if (value < 0) return SubtractMaxValue(-value);

  max_statistic_ = (max_statistic_ + value) > kMaxStatisticValue ? kMaxStatisticValue : max_statistic_ + value;
}

void Statistic::SubtractValue(std::int32_t value) {
  if (value < 0) return AddValue(-value);

  statistic_ = (statistic_ - value) < 0 ? 0 : statistic_ - value;
}

void Statistic::SubtractMaxValue(std::int32_t value) {
  if (value < 0) return AddMaxValue(-value);

  max_statistic_ = (max_statistic_ - value) < 0 ? 0 : max_statistic_ - value;
  statistic_ = statistic_ > max_statistic_ ? max_statistic_ : statistic_;
}

std::int32_t Statistic::GetValue() const {
  return statistic_;
}

std::int32_t Statistic::GetMaxValue() const {
  return max_statistic_;
}

double Statistic::GetPercent() const {
  return static_cast<double>(statistic_) / static_cast<double>(max_statistic_);
}

StatisticType Statistic::GetType() const {
  return statistic_type_;
}

bool Statistic::operator==(const Statistic &rhs) {
  return statistic_type_ == rhs.statistic_type_;
}

bool Statistic::operator!=(const Statistic &rhs) {
  return !(*this == rhs);
}

void Statistic::Set(int32_t max_value, int32_t value) {
  SetMaxValue(max_value);
  SetValue(value);
}
