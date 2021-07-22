#ifndef IATTRIBUTESHANDLER_HPP
#define IATTRIBUTESHANDLER_HPP

#include "../game_core/Attribute.hpp"
class IAttributesHandler {
 public:
  virtual ~IAttributesHandler() = default;
  virtual void OnAttributesUpdate(const std::vector<std::unique_ptr<Attribute>> &attributes) = 0;
  virtual void OnAttributeUpdate(const std::unique_ptr<Attribute> &attribute) = 0;
};

#endif //IATTRIBUTESHANDLER_HPP
