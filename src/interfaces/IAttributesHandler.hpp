#ifndef IATTRIBUTESHANDLER_HPP
#define IATTRIBUTESHANDLER_HPP

class Attribute;
class IAttributesHandler {
 public:
  virtual void OnAttributesUpdate(const std::vector<std::unique_ptr<Attribute>> &attributes) = 0;
  virtual void OnAttributeUpdate(const std::unique_ptr<Attribute> &attribute) = 0;
};

#endif //IATTRIBUTESHANDLER_HPP
