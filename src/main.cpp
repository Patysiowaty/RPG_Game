#include "game_core/Game.hpp"
#include <iostream>

int main() try {
  Game game;
  game.InitializeResources();
  game.Run();

  return EXIT_SUCCESS;
} catch (std::exception &e) {
  std::cerr << "An error has occurred: " << e.what() << "\n";
  return EXIT_FAILURE;
}
