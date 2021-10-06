#ifndef ITEMSLOT_HPP
#define ITEMSLOT_HPP
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Window.hpp"
#include "../views/ItemView.hpp"
#include "../interfaces/IGameWindow.hpp"
#include "../models/Player.hpp"
#include "../SlotIndex.hpp"

class ItemSlot : public Window {
 public:
  explicit ItemSlot(Window *parent = nullptr);

  void Deserialize(const boost::property_tree::ptree &ptree) override;
  void SetPosition(const sf::Vector2f &new_position) override;
  void Move(const sf::Vector2f &offset) override;
  void Update(float delta_time) override;
  void Activate() override;
  void Deactivate() override;
  void RestoreDefault() override;

  void PutItem(std::unique_ptr<ItemView> item_view);
  void TakeOutItem();
  const std::unique_ptr<ItemView> &GetItemView() const { return item_view_; }

  bool IsEmpty() const;

 private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

 private:
  Window *parent_{nullptr};
  std::unique_ptr<ItemView> item_view_;
  const sf::Vector2f item_position_offset_{2.f, 2.f};
};

#endif //ITEMSLOT_HPP
