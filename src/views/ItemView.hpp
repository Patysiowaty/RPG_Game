#ifndef ITEMVIEW_HPP
#define ITEMVIEW_HPP

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "../item_types/Item.hpp"
#include "../ui_elements/Window.hpp"

class ItemTipView : public Window {
 public:
  explicit ItemTipView(const std::shared_ptr<Item> &item) : item_{item} {
	Window::SetSize({100, 200});
	Window::SetFillColor({128, 128, 128, 180});
  }

 private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
	Window::draw(target, states);
  }

 private:
  const std::shared_ptr<Item> &item_;
};

class ItemView : public Window {
 public:
  ItemView() = default;
  explicit ItemView(const std::shared_ptr<Item> &item);

  void FillData(const std::shared_ptr<Item> &item);
  void SetTipVisibility(bool visibility);
  void Move(const sf::Vector2f &offset) override;
  void SetPosition(const sf::Vector2f &new_position) override;

 private:
  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

 private:
  bool tip_visible_{false};
  ItemTipView item_tip_view_;
};

#endif //ITEMVIEW_HPP
