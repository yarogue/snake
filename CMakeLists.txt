cmake_minimum_required(VERSION 3.16)
project(snake)

set(CMAKE_CXX_STANDARD 20)

# Default to Debug build
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# --- Fetch raylib ---
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_SHALLOW TRUE
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

# --- Main executable ---
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
target_link_libraries(snake PRIVATE raylib)

# --- Copy data files to build directory (desktop) ---
add_custom_command(TARGET snake POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:snake>/data
)

# --- Web (Emscripten) build ---
if(EMSCRIPTEN)
  set_target_properties(snake PROPERTIES SUFFIX ".html")
  target_link_options(snake PRIVATE
      -sUSE_GLFW=3
      -sASSERTIONS=1
      -sWASM=1
      -sALLOW_MEMORY_GROWTH=1
      --preload-file ${CMAKE_SOURCE_DIR}/data@data
      --shell-file ${CMAKE_SOURCE_DIR}/web/shell.html
  )
  # Copy output to web-ready directory
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()
