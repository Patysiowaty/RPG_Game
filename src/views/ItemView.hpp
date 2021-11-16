#ifndef ITEMVIEW_HPP
#define ITEMVIEW_HPP
#include "ItemTipView.hpp"

class ItemView : public Window {
 public:
  explicit ItemView(const std::shared_ptr<Item> &item);

  void FillData(const std::shared_ptr<Item> &item);
  void Move(const sf::Vector2f &offset) override;
  void SetPosition(const sf::Vector2f &new_position) override;
  void Update(float delta_time) override;
  std::uint32_t GetItemId() const { return item_id_; }

 private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

 private:
  std::uint32_t item_id_;
  ItemTipView item_tip_view_;
};

#endif //ITEMVIEW_HPP
