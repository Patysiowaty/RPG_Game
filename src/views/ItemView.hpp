#ifndef ITEMVIEW_HPP
#define ITEMVIEW_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../item_types/Item.hpp"
class ItemTipView : private sf::Drawable {
 public:
  explicit ItemTipView(const std::shared_ptr<Item> &item) : item_{item} {}

 private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {}

 private:
  const std::shared_ptr<Item> &item_;
};

class ItemView : public sf::Drawable {
 public:
  ItemView() = default;
  explicit ItemView(const std::shared_ptr<Item> &item);

  void FillData(const std::shared_ptr<Item> &item);
  void SetTipVisibility(bool visibility);
  void Move(const sf::Vector2f &offset);
  void SetPosition(const sf::Vector2f &new_position);

 private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

 private:
  bool tip_visible_;
  sf::Texture item_texture_;
  sf::Sprite sprite_;
  sf::Transformable transform_;
};

#endif //ITEMVIEW_HPP
