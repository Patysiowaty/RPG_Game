#ifndef PLAYGAMESTATE_HPP
#define PLAYGAMESTATE_HPP
#include "interfaces/IGameState.hpp"

class PlayGameState : public IGameState {
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

#endif //PLAYGAMESTATE_HPP
