#ifndef IRANGEVALUECONTAINER_HPP
#define IRANGEVALUECONTAINER_HPP
#include "IBaseValueContainer.hpp"
template<class T>
class IRangeValueContainer : public IBaseValueContainer<T> {
 public:
  virtual void SetValue(T value) = 0;
  virtual void AddValue(T value) = 0;
  virtual void SubtractValue(T value) = 0;
  virtual T GetValue() const = 0;

  virtual void Set(T max_value, T value) = 0;

  virtual void SetMaxValue(T value) = 0;
  virtual void AddMaxValue(T value) = 0;
  virtual void SubtractMaxValue(T value) = 0;
  virtual T GetMaxValue() const = 0;

  virtual double GetPercent() const = 0;
};

#endif //IRANGEVALUECONTAINER_HPP
