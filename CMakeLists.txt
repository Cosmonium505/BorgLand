cmake_minimum_required(VERSION 3.14)

project(BorgLand VERSION 0.1.0 LANGUAGES CXX)

set(BORGLAND_SOURCE_FILES
    src/main.cpp
)

include_directories(include)

enable_testing()

add_executable(BorgLand ${BORGLAND_SOURCE_FILES})

set_target_properties(BorgLand PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)