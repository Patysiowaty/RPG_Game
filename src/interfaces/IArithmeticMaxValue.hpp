#ifndef IARITHMETICMAXVALUE_HPP
#define IARITHMETICMAXVALUE_HPP
template<class T>
class IArithmeticMaxValue {
 public:
  virtual ~IArithmeticMaxValue() = default;
  virtual void AddMaxValue(T value) = 0;
  virtual void SubtractMaxValue(T value) = 0;
};

#endif //IARITHMETICMAXVALUE_HPP
