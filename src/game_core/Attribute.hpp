#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP
#include "../interfaces/IBaseValueContainer.hpp"
#include "../interfaces/ISingleArithmeticValue.hpp"
#include <cstdint>
#include "../enums/AttributeType.hpp"

class Attribute : public IBaseValueContainer<std::int32_t>, public ISingleArithmeticValue<std::int32_t> {
 public:
  explicit Attribute(AttributeType attribute_type, std::int32_t value = 0);

  void SetValue(std::int32_t value) override;
  void AddValue(std::int32_t value) override;
  void SubtractValue(std::int32_t value) override;

  std::int32_t GetValue() const override;
  AttributeType GetType() const;

  bool operator==(const Attribute &rhs);
  bool operator!=(const Attribute &rhs);
  Attribute &operator+=(const Attribute &rhs);
  Attribute &operator-=(const Attribute &rhs);
  Attribute operator+(const Attribute &rhs);
  Attribute operator-(const Attribute &rhs);

 private:
  static constexpr std::int32_t kMaxAttributeValue = 999999;
  AttributeType attribute_type_ = AttributeType::kNone;
  std::int32_t attribute_{0};
};

#endif //ATTRIBUTE_HPP
