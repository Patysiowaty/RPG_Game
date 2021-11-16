#ifndef ITEMTIPVIEW_HPP
#define ITEMTIPVIEW_HPP

#include "../item_types/Item.hpp"
#include "../ui_elements/Label.hpp"

class ItemTipView : public Window {
 public:
  ItemTipView();
  explicit ItemTipView(const std::shared_ptr<Item> &item);

  void SetPosition(const sf::Vector2f &new_position) override;
  void FillData(const std::shared_ptr<Item> &item);

 private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  void SetLabels();

  std::string ParseAttribute(const Attribute &attribute);
  std::string ParseStatistic(const Statistic &statistic);
  std::string ParseRarities(ItemRarity rarity);

 private:
  std::vector<Label> stats_labels_;
  sf::Color rarity_color_;
};

#endif //ITEMTIPVIEW_HPP
