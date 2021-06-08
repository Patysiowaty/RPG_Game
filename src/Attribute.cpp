#include "Attribute.hpp"

Attribute::Attribute(AttributeType attribute_type, std::int32_t value) : attribute_type_{attribute_type},
																		 attribute_{value} {
}

void Attribute::SetValue(int value) {

}

void Attribute::AddValue(int value) {
  if (value < 0) SubtractValue(-value);

  attribute_ = (attribute_ + value) > kMaxAttributeValue ? kMaxAttributeValue : attribute_ + value;
}

void Attribute::SubtractValue(int value) {
  if (value < 0) AddValue(-value);

  attribute_ = (attribute_ - value) < 0 ? 0 : attribute_ + value;
}

std::int32_t Attribute::GetValue() const {
  return attribute_;
}

AttributeType Attribute::GetType() const {
  return attribute_type_;
}

bool Attribute::operator==(const Attribute &rhs) {
  return attribute_type_ == rhs.attribute_type_;
}

bool Attribute::operator!=(const Attribute &rhs) {
  return !(*this == rhs);
}

Attribute &Attribute::operator+=(const Attribute &rhs) {
  attribute_ += rhs.attribute_;
  return *this;
}

Attribute &Attribute::operator-=(const Attribute &rhs) {
  attribute_ -= rhs.attribute_;
  return *this;
}

Attribute Attribute::operator+(const Attribute &rhs) {
  return Attribute(attribute_type_, attribute_ + rhs.attribute_);
}

Attribute Attribute::operator-(const Attribute &rhs) {
  return Attribute(attribute_type_, attribute_ - rhs.attribute_);
}

