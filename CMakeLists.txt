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
src/controller.cpp)

include_directories(include)

enable_testing()

if(WIN32)
    set(CMAKE_GENERATOR_PLATFORM x64)
    set(CMAKE_GENERATOR "Visual Studio 17 2022")
    set(CMAKE_SYSTEM_VERSION 10.0)

    if(DEFINED ENV{VCPKG_ROOT})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
    endif()
endif()

add_executable(BorgLand ${BORGLAND_SOURCE_FILES})
if(MSVC)
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
    target_compile_options(BorgLand PRIVATE /MT)
    target_link_options(BorgLand PRIVATE /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
endif()

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