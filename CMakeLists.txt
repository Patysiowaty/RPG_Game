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

add_executable(RPG_Game src/main.cpp src/GameCore.cpp src/GameCore.hpp src/Character.cpp src/Character.hpp src/enums/CharacterGender.hpp src/enums/CharacterRace.hpp src/enums/CharacterClass.hpp src/CharacterAttributes.cpp src/CharacterAttributes.hpp src/Player.cpp src/Player.hpp src/item_types/Item.cpp src/item_types/Item.hpp src/CharacterEquipment.cpp src/CharacterEquipment.hpp src/enums/ItemType.hpp src/CharacterInventory.cpp src/CharacterInventory.hpp src/PlayerExperience.cpp src/PlayerExperience.hpp src/CharacterLevel.cpp src/CharacterLevel.hpp src/item_types/SwordItem.cpp src/item_types/SwordItem.hpp src/ItemTemplate.cpp src/ItemTemplate.hpp src/enums/ItemLocation.hpp src/enums/ErrorCodes/ItemManagerEC.hpp src/CharacterStatistics.cpp src/CharacterStatistics.hpp src/item_types/ConsumptiveItem.cpp src/item_types/ConsumptiveItem.hpp src/enums/ItemRarity.hpp src/ItemManager.hpp src/ItemManager.cpp src/IItemHandler.hpp src/IItemHandler.cpp src/IItemList.hpp src/CharacterDataUpdater.hpp src/CharacterDataUpdater.cpp src/ILevelHandler.hpp src/LevelManager.cpp src/LevelManager.hpp src/enums/ErrorCodes/LevelManagerEC.hpp)

target_link_libraries(${PROJECT_NAME} PRIVATE libbcrypt.a)
