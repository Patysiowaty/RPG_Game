#ifndef IPUBLISHER_HPP
#define IPUBLISHER_HPP

template<class T>
class IPublisher {
 public:
  virtual void RegisterHandler(T *value) = 0;
};

#endif //IPUBLISHER_HPP
