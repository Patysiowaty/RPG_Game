#ifndef IMAXVALUECONTAINER_HPP
#define IMAXVALUECONTAINER_HPP

template<class T>
class IMaxValueContainer {
 public:
  virtual ~IMaxValueContainer() = default;
  virtual void SetMaxValue(T value) = 0;
  virtual T GetMaxValue() const = 0;
};

#endif //IMAXVALUECONTAINER_HPP
