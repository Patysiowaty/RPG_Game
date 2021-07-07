#include "ConsoleView.hpp"
void ConsoleView::DrawText(const std::string &text, const Position<std::uint32_t> &position, Color color) {
  std::cout << text << "\n";
  system("cls");
}
