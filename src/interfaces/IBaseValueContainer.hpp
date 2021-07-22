#ifndef IBASEVALUECONTAINER_HPP
#define IBASEVALUECONTAINER_HPP

template<class T>
class IBaseValueContainer {
 public:
  virtual ~IBaseValueContainer() = default;
  virtual void SetValue(T value) = 0;
  virtual T GetValue() const = 0;
};

#endif //IBASEVALUECONTAINER_HPP
