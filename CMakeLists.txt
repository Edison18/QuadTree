cmake_minimum_required(VERSION 3.8)
project(Game_of_Life)

set(CMAKE_CXX_STANDARD 14)


include_directories("${CMAKE_CURRENT_LIST_DIR}/src")
add_subdirectory(src)

include("src/sources.cmake")

add_executable(Game_of_Life ${sources} src/main.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Game_of_Life ${SFML_LIBRARIES})
endif()
