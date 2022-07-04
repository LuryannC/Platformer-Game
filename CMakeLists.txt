cmake_minimum_required(VERSION 3.14)
project(PlatformerSFML)

set(CMAKE_CXX_STANDARD 14)

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()


find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)
set(SOURCE_FILES src/main.cpp src/Game.cpp src/Game.h src/State.cpp src/State.h src/Functions.cpp src/Functions.h src/GameState/MainMenu.cpp src/GameState/MainMenu.h src/GameObject/Player.cpp src/GameObject/Player.h src/GameObject/Maps.cpp src/GameObject/Maps.h src/StateEnum.h src/GameObject/GameObjects.cpp src/GameObject/GameObjects.h src/GameObject/Entities/Enemy.cpp src/GameObject/Entities/Enemy.h src/GameState/GamePlay.cpp src/GameState/GamePlay.h src/GameState/GameOver.cpp src/GameState/GameOver.h src/GameState/Tutorial.cpp src/GameState/Tutorial.h src/GameState/GameWin.cpp src/GameState/GameWin.h src/GameState/LeveLSelector.cpp src/GameState/LeveLSelector.h)
add_executable(PlatformerSFML ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

target_link_libraries (PlatformerSFML sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Data/)