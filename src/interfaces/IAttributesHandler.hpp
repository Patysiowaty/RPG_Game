#ifndef IATTRIBUTESHANDLER_HPP
#define IATTRIBUTESHANDLER_HPP
#include "../enums/AttributeType.hpp"

class IAttributesHandler {
 public:
  virtual void OnAttributesRaise() = 0;
  virtual void OnAttributesLower() = 0;
  virtual void OnAttributeRaise(AttributeType attribute_type) = 0;
  virtual void OnAttributeLower(AttributeType attribute_type) = 0;
};

#endif //IATTRIBUTESHANDLER_HPP
