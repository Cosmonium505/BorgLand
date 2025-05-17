cmake_minimum_required(VERSION 3.14)

project(LevelEditor VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base aui adv)
include(${wxWidgets_USE_FILE})

include_directories(include)
include_directories(../include)

add_executable(LevelEditor
    src/main.cpp
)

target_link_libraries(LevelEditor PRIVATE ${wxWidgets_LIBRARIES})
