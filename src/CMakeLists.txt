cmake_minimum_required(VERSION 3.8)
project(QuadTree)

set(CMAKE_CXX_STANDARD 14)

execute_process(COMMAND ${CMAKE_COMMAND}
        -D "RDIR=${CMAKE_CURRENT_SOURCE_DIR}"
        -P "scansources.cmake"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")