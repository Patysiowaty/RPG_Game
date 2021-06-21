#ifndef RANGESTATISTIC_HPP
#define RANGESTATISTIC_HPP

#include "interfaces/IMaxValueContainer.hpp"
#include "SingleStatistic.hpp"
#include "interfaces/IArithmeticMaxValue.hpp"

class RangeStatistic : public SingleStatistic, public IMaxValueContainer<std::int32_t>,
	public IArithmeticMaxValue<std::int32_t> {
 public:
  explicit RangeStatistic(StatisticType statistic_type, std::int32_t value = 0, std::int32_t max_value = 0);

  void SetValue(int32_t value) override;
  void SetMaxValue(int32_t value) override;

  void AddValue(int32_t value) override;
  void AddMaxValue(int32_t value) override;
  void SubtractMaxValue(int32_t value) override;

  int32_t GetMaxValue() const override;
  double GetPercentageValue() const override;

 private:
  std::int32_t max_value_{0};
};

#endif //RANGESTATISTIC_HPP
