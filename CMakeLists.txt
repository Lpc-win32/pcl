cmake_minimum_required(VERSION 2.8)

project(pcl)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -std=c++11 -Wall")

include_directories("${PROJECT_SOURCE_DIR}/src")
AUX_SOURCE_DIRECTORY("${PROJECT_SOURCE_DIR}/src" SRC_LIST)

message("Build Static Library")
add_library(pcl STATIC ${SRC_LIST})

set(CMAKE_INSTALL_PREFIX "/usr/local")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/src/" DESTINATION "include/pcl" FILES_MATCHING PATTERN "*.h")
install(FILES "${PROJECT_BINARY_DIR}/pcl.a" DESTINATION "lib")
