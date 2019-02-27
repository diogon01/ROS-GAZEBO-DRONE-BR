cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(vant3D_gazebo)

# Find Gazebo
find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")

# Build our plugin
add_library(velodyne_plugin SHARED src/velodyne_plugin.cpp)
target_link_libraries(velodyne_plugin ${GAZEBO_LIBRARIES})