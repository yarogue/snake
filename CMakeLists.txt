cmake_minimum_required(VERSION 3.16)
project(snake)

set(CMAKE_CXX_STANDARD 20)

# TODO 6b-1: Add all source files to the executable
# As you complete each .cpp file in src/, add it to this list.
add_executable(snake
    main.cpp
    src/Snake.cpp
    src/Board.cpp
    src/Renderer.cpp
    src/InputHandler.cpp
    src/GameEngine.cpp
)

# TODO 6b-2: Add the include/ directory so #include "Foo.hpp" works
target_include_directories(snake PRIVATE include)

# TODO 6b-3: Link the ncurses library
# ncurses handles terminal drawing and non-blocking input.
# Install it first if needed:
#   Ubuntu/Debian: sudo apt install libncurses-dev
#   Fedora/RHEL:   sudo dnf install ncurses-devel
find_package(Curses REQUIRED)
target_link_libraries(snake PRIVATE ${CURSES_LIBRARIES})
target_include_directories(snake PRIVATE ${CURSES_INCLUDE_DIR})
