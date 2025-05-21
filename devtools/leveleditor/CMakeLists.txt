cmake_minimum_required(VERSION 3.14)

project(LevelEditor VERSION 0.1.0 LANGUAGES CXX)

if (UNIX)
    set(CMAKE_TOOLCHAIN_FILE "$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake")
endif()

if (APPLE)
    include_directories(/opt/homebrew/include)
endif()

set(CMAKE_CXX_STANDARD 20)

# Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base aui adv)
include(${wxWidgets_USE_FILE})

include_directories(include)
include_directories(../../include)

set(LEVEL_EDITOR_SOURCE_EXTERN
    ../../src/tileLoader.cpp
    src/elements/blockElement.cpp
    src/elements/editorElement.cpp
)

add_executable(LevelEditor
    src/main.cpp
    src/mainDisplay.cpp
    src/blockSelector.cpp
    src/toolDisplay.cpp
    src/saveLevel.cpp
    ${LEVEL_EDITOR_SOURCE_EXTERN}
)

target_link_libraries(LevelEditor PRIVATE ${wxWidgets_LIBRARIES})

find_package(SDL2 CONFIG REQUIRED)

target_link_libraries(LevelEditor
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)