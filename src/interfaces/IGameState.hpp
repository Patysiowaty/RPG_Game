#ifndef IGAMESTATE_HPP
#define IGAMESTATE_HPP
#include "IViewContext.hpp"

class IGameState {
 public:
  virtual ~IGameState() = default;
  virtual void Initialize() = 0;
  virtual void Draw(IViewContext *view_context, double delta_time) = 0;
  virtual void Update(double delta_time) = 0;
  virtual void HandleEvent() = 0;
  virtual void Cleanup() = 0;
  virtual void Pause() = 0;
  virtual void Resume() = 0;
};

#endif //IGAMESTATE_HPP
