cmake_minimum_required (VERSION 3.4)
project (CPush_Runner)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../libs
)

FILE(GLOB_RECURSE CPP_SOURCES *.cpp)
add_executable(${PROJECT_NAME} ${CPP_SOURCES})

target_link_libraries(${PROJECT_NAME} ssl crypto hiredis)
