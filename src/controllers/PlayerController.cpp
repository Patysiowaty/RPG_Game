#include "PlayerController.hpp"
#include "../managers/InputManager.hpp"
PlayerController::PlayerController(Player &player, PlayerView &player_view) : player_{player},
																			  player_view_{player_view} {
}

void PlayerController::MovePlayer(const sf::Vector2f &velocity, Direction direction) {
  const auto offset = velocity * acceleration_;
  switch (direction) {
	case Direction::kDown:
	  MovePlayerDown(offset);
	  break;
	case Direction::kUp:
	  MovePlayerUp(offset);
	  break;
	case Direction::kLeft:
	  MovePlayerLeft(offset);
	  break;
	case Direction::kRight:
	  MovePlayerRight(offset);
	  break;
  }

  player_.move(offset);

  for (const auto handler : handlers_) {
	handler->OnPlayerMove(offset);
  }
}

void PlayerController::Update(float delta_time) {
  if (InputManager::IsKeyPressed(sf::Keyboard::Key::S) || InputManager::IsKeyPressed(sf::Keyboard::Key::Down)) {
	MovePlayer({kMoveVelocityList[0].x * delta_time, kMoveVelocityList[0].y * delta_time}, Direction::kDown);
  } else if (InputManager::IsKeyPressed(sf::Keyboard::Key::W) || InputManager::IsKeyPressed(sf::Keyboard::Key::Up)) {
	MovePlayer({kMoveVelocityList[1].x * delta_time, kMoveVelocityList[1].y * delta_time}, Direction::kUp);
  } else if (InputManager::IsKeyPressed(sf::Keyboard::Key::A) || InputManager::IsKeyPressed(sf::Keyboard::Key::Left)) {
	MovePlayer({kMoveVelocityList[2].x * delta_time, kMoveVelocityList[2].y * delta_time}, Direction::kLeft);
  } else if (InputManager::IsKeyPressed(sf::Keyboard::Key::D) || InputManager::IsKeyPressed(sf::Keyboard::Key::Right)) {
	MovePlayer({kMoveVelocityList[3].x * delta_time, kMoveVelocityList[3].y * delta_time}, Direction::kRight);
  }

  if (InputManager::IsMouseButtonReleased(sf::Mouse::Left))
	player_view_.OnAttack();


}

void PlayerController::RegisterHandler(IPlayerHandler *value) {
  handlers_.emplace_back(value);
}

void PlayerController::MovePlayerDown(const sf::Vector2f &offset) {
  player_view_.OnMoveDown(offset);
}

void PlayerController::MovePlayerUp(const sf::Vector2f &offset) {
  player_view_.OnMoveUp(offset);
}

void PlayerController::MovePlayerLeft(const sf::Vector2f &offset) {
  player_view_.OnMoveLeft(offset);
}

void PlayerController::MovePlayerRight(const sf::Vector2f &offset) {
  player_view_.OnMoveRight(offset);
}



