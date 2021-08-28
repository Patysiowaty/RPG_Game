#ifndef IUPDATABLE_HPP
#define IUPDATABLE_HPP

class IUpdatable {
 public:
  virtual ~IUpdatable() = default;
  virtual void Update(float delta_time) = 0;
};

#endif //IUPDATABLE_HPP
