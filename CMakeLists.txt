cmake_minimum_required(VERSION 3.14)

project(BorgLand VERSION 0.1.0 LANGUAGES CXX)

if (UNIX)
    set(CMAKE_TOOLCHAIN_FILE "$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake")
endif()

set(BORGLAND_SOURCE_FILES
    src/main.cpp
    src/classes/world.cpp
    src/classes/player.cpp
    src/classes/block.cpp
    src/tileLoader.cpp
)

include_directories(include)

enable_testing()

add_executable(BorgLand ${BORGLAND_SOURCE_FILES})

set_target_properties(BorgLand PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

find_package(SDL2 CONFIG REQUIRED)

target_link_libraries(BorgLand
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)