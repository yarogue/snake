cmake_minimum_required(VERSION 3.16)
project(snake)

set(CMAKE_CXX_STANDARD 20)

add_executable(snake
    main.cpp
    src/Snake.cpp
    src/Board.cpp
    src/Renderer.cpp
    src/InputHandler.cpp
    src/GameEngine.cpp
    src/LevelLoader.cpp
    src/HighScoreManager.cpp
    src/Menu.cpp
    src/LinkedList.cpp
)

target_include_directories(snake PRIVATE include)

find_package(Curses REQUIRED)
target_link_libraries(snake PRIVATE ${CURSES_LIBRARIES})
target_include_directories(snake PRIVATE ${CURSES_INCLUDE_DIR})
