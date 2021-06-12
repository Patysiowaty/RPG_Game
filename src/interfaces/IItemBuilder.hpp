#ifndef IITEMBUILDER_HPP
#define IITEMBUILDER_HPP

#include <string>
class IItemBuilder {
 public:
  virtual bool BuildRawItem() = 0;
  virtual bool BuildItemRequirements() = 0;
  virtual bool BuildAttributes() = 0;
  virtual bool BuildStatistics() = 0;
  virtual bool BuildOptionalData() = 0;
};

#endif //IITEMBUILDER_HPP
