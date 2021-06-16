#ifndef CHARACTERATTRIBUTES_HPP
#define CHARACTERATTRIBUTES_HPP

#include <cstdint>
#include <memory>
#include "interfaces/IItemHandler.hpp"
#include "interfaces/ILevelHandler.hpp"
#include "Attribute.hpp"
#include "interfaces/IPublisher.hpp"
#include "interfaces/IAttributesHandler.hpp"

class CharacterAttributes : public IPublisher<IAttributesHandler> {
 public:
  explicit CharacterAttributes(std::int32_t strength = 0, std::int32_t dexterity = 0, std::int32_t vitality = 0,
							   std::int32_t intelligence = 0);

  std::shared_ptr<Attribute> GetAttribute(AttributeType attribute_type);
  void SetAttributes(const std::vector<std::int32_t> &attributes);

  void RaiseAttributes();
  void LowerAttributes();
  void AddAttribute(AttributeType attribute_type, std::int32_t value = 0);
  void AddAttribute(std::shared_ptr<Attribute> attribute);

  void RegisterHandler(IAttributesHandler *handler) override;

 private:
  static constexpr int16_t kAttributesBaseModifier{3};

  std::vector<std::shared_ptr<Attribute>> attributes_;
  std::vector<IAttributesHandler *> handlers_;
};

#endif //CHARACTERATTRIBUTES_HPP
