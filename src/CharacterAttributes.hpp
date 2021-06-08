#ifndef CHARACTERATTRIBUTES_HPP
#define CHARACTERATTRIBUTES_HPP

#include <cstdint>
#include <memory>
#include "Interfaces/IItemHandler.hpp"
#include "Interfaces/ILevelHandler.hpp"
#include "Attribute.hpp"

class CharacterAttributes {
 public:
  explicit CharacterAttributes(std::int32_t strength = 0, std::int32_t dexterity = 0, std::int32_t vitality = 0,
							   std::int32_t intelligence = 0);

  std::shared_ptr<Attribute> GetAttribute(AttributeType attribute_type);

  void RaiseAttributes();
  void LowerAttributes();

 private:
  static constexpr int16_t kAttributesBaseModifier{3};

  std::vector<std::shared_ptr<Attribute>> attributes_;
};

#endif //CHARACTERATTRIBUTES_HPP
