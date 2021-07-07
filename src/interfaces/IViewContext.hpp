#ifndef IVIEWCONTEXT_HPP
#define IVIEWCONTEXT_HPP
#include <string>
template<typename T>
struct Position {
  T pos_x{0};
  T pos_y{0};
};

enum class Color {
  kWhite, kRed, kBlue, kGreen
};

class IViewContext {
 public:
  virtual void DrawText(const std::string &text, const Position<std::uint32_t> &position,
						Color color = Color::kWhite) = 0;
};

#endif //IVIEWCONTEXT_HPP
