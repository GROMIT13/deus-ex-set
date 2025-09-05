cmake_minimum_required(VERSION 3.0)
project(deus_ex_set CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

# Adding our source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp") # Define PROJECT_SOURCES as a list of all source files
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/src/*.hpp") # Define PROJECT_SOURCES as a list of all source files
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/src/") # Define PROJECT_INCLUDE to be the path to the include directory of the project
include_directories("${CMAKE_SOURCE_DIR}/src/entities")
include_directories("${CMAKE_SOURCE_DIR}/src/entities/player")
include_directories("${CMAKE_SOURCE_DIR}/src/entities/bullet")
include_directories("${CMAKE_SOURCE_DIR}/src/vec")
include_directories("${CMAKE_SOURCE_DIR}/src/window")
include_directories("${CMAKE_SOURCE_DIR}/src/space")
include_directories("${CMAKE_SOURCE_DIR}/src/scenes")
include_directories("${CMAKE_SOURCE_DIR}/src/scenes/gameScenes")
include_directories("${CMAKE_SOURCE_DIR}/src/test")
include_directories("${CMAKE_SOURCE_DIR}/src/graphics")

# Declaring our executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES} "src/entities/entity.cpp" "src/entities/player/player.cpp" "src/scenes/baseScene.cpp" "src/entities/bullet/bullet.cpp" "src/entities/bullet/bulletManager.cpp" "src/scenes/baseLevel.cpp" "src/graphics/spriteManager.cpp" "src/graphics/sprite.cpp" "src/entities/player/playerS.cpp" "src/entities/player/playerP.cpp" "src/graphics/draw.cpp" "src/window/window.cpp" "src/scenes/gameScenes/menu.cpp")
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Setting ASSETS_PATH
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/") # Set the asset path macro to the absolute path on the dev machine
target_compile_definitions(deus_ex_set PUBLIC -DFPS=60 )
#target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets") # Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable