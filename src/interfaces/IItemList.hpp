#ifndef IITEMLIST_HPP
#define IITEMLIST_HPP

class IItemList {
 public:
  virtual bool PutItem(std::shared_ptr<Item> item) = 0;
  virtual bool RemoveItem(std::shared_ptr<Item> item) = 0;
};

#endif //IITEMLIST_HPP
