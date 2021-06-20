#include "Player.hpp"
#include "JsonSerializer.hpp"
#include "ItemBuilder.hpp"
int main() {
  ItemBuilder item_builder(1);
  JSONSerializer serializer;
  Player player;
  player.GetLevel().SetLevel(20);

  //serializer.LoadAndDeserialize(&player, "../game_data/test.json");

}