cmake_minimum_required(VERSION 3.16)
project(snake)

set(CMAKE_CXX_STANDARD 20)

# Default to Debug build (needed for debugger symbols)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

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

# --- Cross-platform curses handling ---
if(WIN32)
  # Build PDCurses from source (wincon backend for Windows Console)
  file(GLOB PDCURSES_CORE_SRCS   deps/pdcurses/pdcurses/*.c)
  file(GLOB PDCURSES_WINCON_SRCS deps/pdcurses/wincon/*.c)

  add_library(pdcurses STATIC ${PDCURSES_CORE_SRCS} ${PDCURSES_WINCON_SRCS})
  target_include_directories(pdcurses PUBLIC deps/pdcurses)
  target_include_directories(pdcurses PRIVATE deps/pdcurses/wincon)
  target_compile_definitions(pdcurses PRIVATE PDC_WIDE)

  target_link_libraries(snake PRIVATE pdcurses)
  target_include_directories(snake PRIVATE deps/pdcurses)

  # Static link MinGW runtime so the exe doesn't need DLLs
  target_link_options(snake PRIVATE -static)
else()
  # Linux / macOS — use system ncurses
  find_package(Curses REQUIRED)
  target_link_libraries(snake PRIVATE ${CURSES_LIBRARIES})
  target_include_directories(snake PRIVATE ${CURSES_INCLUDE_DIR})
endif()
