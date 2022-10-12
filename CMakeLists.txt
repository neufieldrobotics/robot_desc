cmake_minimum_required(VERSION 3.0.2)
project(robot_desc)

add_compile_options(-std=c++17)

find_package(catkin REQUIRED COMPONENTS
  dynamic_reconfigure
  std_msgs
  sensor_msgs
  geometry_msgs
  roscpp
  tf2
  tf2_ros
  tf2_geometry_msgs
)
generate_dynamic_reconfigure_options(
  cfg/dynamic_params.cfg
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS
    roscpp std_msgs sensor_msgs geometry_msgs
)

add_executable(robot_static_tf_publisher src/robot_static_tf_publisher.cpp)
target_link_libraries(robot_static_tf_publisher ${catkin_LIBRARIES})
add_dependencies(robot_static_tf_publisher ${PROJECT_NAME}_gencfg)

install(TARGETS robot_static_tf_publisher
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
install(DIRECTORY launch
   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

install(DIRECTORY include
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
  PATTERN ".svn" EXCLUDE
)


