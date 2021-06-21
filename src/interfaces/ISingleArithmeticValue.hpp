#ifndef ISINGLEARITHMETICVALUE_HPP
#define ISINGLEARITHMETICVALUE_HPP

template<class T>
class ISingleArithmeticValue {
 public:
  virtual void AddValue(T value) = 0;
  virtual void SubtractValue(T value) = 0;
};

#endif //ISINGLEARITHMETICVALUE_HPP
