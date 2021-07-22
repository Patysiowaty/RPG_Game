#ifndef CHARACTERSTATISTIC_HPP
#define CHARACTERSTATISTIC_HPP

#include "../interfaces/IMaxValueContainer.hpp"
#include "../interfaces/IArithmeticMaxValue.hpp"
#include "../interfaces/ISingleArithmeticValue.hpp"
#include "../interfaces/IStatistic.hpp"

class CharacterStatistic : public IStatistic, public IMaxValueContainer<std::int32_t>,
	public IArithmeticMaxValue<std::int32_t>, public ISingleArithmeticValue<std::int32_t> {
 public:
  explicit CharacterStatistic(StatisticType statistic_type, std::int32_t max_value = 0, std::int32_t value = 0);

  void SetValue(std::int32_t value) override;
  void SetMaxValue(std::int32_t value) override;

  void AddValue(std::int32_t value) override;
  void AddMaxValue(std::int32_t value) override;
  void SubtractValue(int32_t value) override;
  void SubtractMaxValue(std::int32_t value) override;

  std::int32_t GetValue() const override;
  std::int32_t GetMaxValue() const override;
  double GetPercentageValue() const override;
  StatisticType GetType() const override;

 private:
  constexpr static std::int32_t kMaxValue{999999};
  StatisticType statistic_type_;
  std::int32_t value_{0};
  std::int32_t max_value_{0};
};

#endif //CHARACTERSTATISTIC_HPP
