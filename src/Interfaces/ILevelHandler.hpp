#ifndef ILEVELHANDLER_HPP
#define ILEVELHANDLER_HPP

class ILevelHandler {
 public:
  virtual void OnLevelRaise() = 0;
  virtual void OnLevelDowngrade() = 0;
  virtual void OnLevelUpdate(int value) = 0;
};

#endif //ILEVELHANDLER_HPP
