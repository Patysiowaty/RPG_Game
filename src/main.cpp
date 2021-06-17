#include "Player.hpp"
#include "JsonSerializer.hpp"

int main() {
  JSONSerializer json_serializer;
  Player player;
  json_serializer.LoadAndDeserialize(&player, "../game_data/player_data.json");


}