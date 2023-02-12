add_library(robot_modifier RobotModifier.cpp)
target_include_directories(robot_modifier PUBLIC
                                ${OpenRAVE_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/inc)
set_target_properties(robot_modifier PROPERTIES COMPILE_FLAGS "${OpenRAVE_CXX_FLAGS}")
set_target_properties(robot_modifier PROPERTIES LINK_FLAGS "${OpenRAVE_LINK_FLAGS}")
target_link_libraries(robot_modifier sys http_server)
install(TARGETS robot_modifier)