#ifndef CONSOLEVIEW_HPP
#define CONSOLEVIEW_HPP

#include "interfaces/IViewContext.hpp"
#include <iostream>
class ConsoleView : public IViewContext {
 public:
  void DrawText(const std::string &text, const Position<std::uint32_t> &position, Color color = Color::kWhite) override;

};

#endif //CONSOLEVIEW_HPP
