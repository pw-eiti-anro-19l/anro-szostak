cmake_minimum_required(VERSION 2.8.3)
project(lab2)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
  tf
  kdl_conversions
  kdl_parser
)


catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES lab2
#  CATKIN_DEPENDS kdl_parser roscpp tf urdf
#  DEPENDS system_lib
)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

include_directories(include ${catkin_INCLUDE_DIRS})
add_executable(dh2rpy src/dh2rpy.cpp)
target_link_libraries(dh2rpy ${catkin_LIBRARIES})
