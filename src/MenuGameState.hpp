#ifndef MENUGAMESTATE_HPP
#define MENUGAMESTATE_HPP

#include "interfaces/IGameState.hpp"
class MenuGameState : public IGameState {
 public:
  void Initialize() override;
  void Draw(double delta_time) override;
  void Update(double delta_time) override;
  void HandleEvent() override;
  void Cleanup() override;
  void Pause() override;
  void Resume() override;

 private:
  bool active_{true};

};

#endif //MENUGAMESTATE_HPP
