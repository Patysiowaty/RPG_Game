#ifndef PLAYERATTRIBUTES_HPP
#define PLAYERATTRIBUTES_HPP

#include <cstdint>
#include <memory>
#include "interfaces/IItemHandler.hpp"
#include "interfaces/ILevelHandler.hpp"
#include "Attribute.hpp"
#include "interfaces/IPublisher.hpp"
#include "interfaces/IAttributesHandler.hpp"

class PlayerAttributes : public IPublisher<IAttributesHandler>, public IItemHandler, public ILevelHandler {
 public:
  explicit PlayerAttributes(std::int32_t strength = 0, std::int32_t dexterity = 0, std::int32_t vitality = 0,
							std::int32_t intelligence = 0);

  std::shared_ptr<Attribute> GetAttribute(AttributeType attribute_type);
  void SetAttributes(const std::vector<std::int32_t> &attributes);

  void RaiseAttributes();
  void DowngradeAttributes();
  void AddAttribute(AttributeType attribute_type, std::int32_t value = 0);
  void AddAttribute(std::shared_ptr<Attribute> attribute);

  void OnEquipItem(const std::shared_ptr<Item> &item) override;
  void OnTakeOffItem(const std::shared_ptr<Item> &item) override;
  void OnUsedItem(const std::shared_ptr<Item> &item) override;
  void OnLevelRaise() override;
  void OnLevelDowngrade() override;
  void OnLevelUpdate(int value) override;

  void RegisterHandler(IAttributesHandler *handler) override;

 private:
  static constexpr int16_t kAttributesBaseModifier{1};

  std::vector<std::shared_ptr<Attribute>> attributes_;
  std::vector<IAttributesHandler *> handlers_;
};

#endif //PLAYERATTRIBUTES_HPP
