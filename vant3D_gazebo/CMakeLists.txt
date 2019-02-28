cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(vant3D_gazebo)

#Adicionando os plugins ROS
find_package(roscpp REQUIRED)
find_package(std_msgs REQUIRED)
include_directories(${roscpp_INCLUDE_DIRS})
include_directories(${std_msgs_INCLUDE_DIRS})

# Find Gazebo
find_package(gazebo REQUIRED)
include_directories(${GAZEBO_INCLUDE_DIRS})
link_directories(${GAZEBO_LIBRARY_DIRS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")


# Build the stand-alone test program
add_executable(velocidade src/velocidade_velodyne.cc)

if (${gazebo_VERSION_MAJOR} LESS 6)
    # These two
    include(FindBoost)
    find_package(Boost ${MIN_BOOST_VERSION} REQUIRED system filesystem regex)
    target_link_libraries(velocidade ${GAZEBO_LIBRARIES} ${Boost_LIBRARIES})
else ()
    target_link_libraries(velocidade ${GAZEBO_LIBRARIES})
endif ()

# Build our plugin
add_library(velodyne_plugin SHARED src/velodyne_plugin.cc)
target_link_libraries(velodyne_plugin ${GAZEBO_LIBRARIES} ${roscpp_LIBRARIES})