#include "PlayerController.hpp"
#include "../managers/InputManager.hpp"
PlayerController::PlayerController(Player &player, PlayerView &player_view) : player_{player},
																			  player_view_{player_view},
																			  interactor_{player_} {
  interactor_.RegisterHandler(&player_view_);
}

void PlayerController::MovePlayer(const sf::Vector2f &velocity, Direction direction) {
  const auto offset = velocity * acceleration_;

  player_view_.OnMove(direction);
  player_.move(offset);

  for (const auto handler: handlers_) {
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

bool PlayerController::EquipItem(std::uint32_t item_id) {
  auto item = player_.GetPlayerInventory().GetItem(item_id);
  auto ec = interactor_.EquipItem(item);

  return ec == ItemInteractorErrorCode::kNone;
}

bool PlayerController::TakeOffItem(ItemType item_type) {
  auto item = player_.GetPlayerEquipment().GetItemAtSlot(item_type);
  auto ec = interactor_.TakeOffItem(item);

  return ec == ItemInteractorErrorCode::kNone;
}

bool PlayerController::AddItem(std::shared_ptr<Item> item) {
  auto ec = interactor_.AddItem(item);
  return ec == ItemInteractorErrorCode::kNone;
}



