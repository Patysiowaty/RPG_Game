#ifndef IPUBLISHER_HPP
#define IPUBLISHER_HPP

template<class T>
class IPublisher {
 public:
  virtual ~IPublisher() = default;
  virtual void RegisterHandler(T *value) = 0;
};

#endif //IPUBLISHER_HPP
