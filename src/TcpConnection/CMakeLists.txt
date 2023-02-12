add_library(tcp_connection TcpConnection.cpp)
target_include_directories(tcp_connection PUBLIC
                                ${OpenRAVE_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/inc)
set_target_properties(tcp_connection PROPERTIES COMPILE_FLAGS "${OpenRAVE_CXX_FLAGS}")
set_target_properties(tcp_connection PROPERTIES LINK_FLAGS "${OpenRAVE_LINK_FLAGS}")
target_link_libraries(tcp_connection sys)
install(TARGETS tcp_connection)
