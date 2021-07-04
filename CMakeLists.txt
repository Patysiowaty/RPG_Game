cmake_minimum_required(VERSION 3.19)
project(RPG_Game)
set(CMAKE_CXX_STANDARD 20)

if (WIN32)
    message("Detected Windows system")
    set(Boost_INCLUDE_DIR c:/Program\ Files/boost/boost_1_76_0/)
    set(Boost_LIBRARY_DIR c:/Program\ Files/boost/boost_1_76_0/stage/lib/)
elseif (UNIX)
    message("Detected UNIX like system")
    set(Boost_INCLUDE_DIRS /usr/local/boost_1_76_0/include/)
    set(Boost_LIBRARIES /usr/local/lib/)
endif ()

find_package(Boost 1.76.0)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(RPG_Game src/main.cpp src/Game.cpp src/Game.hpp src/interfaces/ICharacter.hpp src/enums/CharacterGender.hpp src/enums/CharacterRace.hpp src/enums/CharacterClass.hpp src/PlayerAttributes.cpp src/PlayerAttributes.hpp src/Player.cpp src/Player.hpp src/item_types/Item.cpp src/item_types/Item.hpp src/PlayerEquipment.cpp src/PlayerEquipment.hpp src/enums/ItemType.hpp src/PlayerInventory.cpp src/PlayerInventory.hpp src/PlayerLevel.cpp src/PlayerLevel.hpp src/item_types/SwordItem.cpp src/item_types/SwordItem.hpp src/enums/ItemLocation.hpp src/enums/ErrorCodes/ItemInteractorErrorCode.hpp src/PlayerStatistics.cpp src/PlayerStatistics.hpp src/item_types/ConsumptiveItem.cpp src/item_types/ConsumptiveItem.hpp src/enums/ItemRarity.hpp src/ItemsInteractor.hpp src/ItemsInteractor.cpp src/interfaces/IItemHandler.hpp src/interfaces/IItemList.hpp src/interfaces/ILevelHandler.hpp src/enums/ErrorCodes/LevelManagerEC.hpp src/interfaces/IBaseValueContainer.hpp src/Attribute.cpp src/Attribute.hpp src/enums/AttributeType.hpp src/enums/StatisticType.hpp src/interfaces/IPublisher.hpp src/interfaces/IItemBuilder.hpp src/ItemBuilder.cpp src/ItemBuilder.hpp src/interfaces/IAttributesHandler.hpp src/interfaces/ICharacterBuilder.hpp src/interfaces/IjsonSerializable.hpp src/JsonSerializer.cpp src/JsonSerializer.hpp src/interfaces/ICharacterClass.hpp src/interfaces/IConsumable.hpp src/interfaces/IStatistic.hpp src/Statistic.cpp src/Statistic.hpp src/interfaces/ISingleArithmeticValue.hpp src/interfaces/IMaxValueContainer.hpp src/SinglePlayerStatistic.cpp src/SinglePlayerStatistic.hpp src/interfaces/IArithmeticMaxValue.hpp src/PlayerController.cpp src/PlayerController.hpp src/GameStatesManager.cpp src/GameStatesManager.hpp src/interfaces/IGameStateHandler.hpp src/interfaces/IGameState.hpp src/MenuGameState.cpp src/MenuGameState.hpp src/PlayGameState.cpp src/PlayGameState.hpp src/Npc.cpp src/Npc.hpp)

target_link_libraries(${PROJECT_NAME} PRIVATE libbcrypt.a)
