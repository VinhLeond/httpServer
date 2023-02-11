add_library(tcp_client Client.cpp)
target_include_directories(tcp_client PUBLIC
                                ${OpenRAVE_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/inc)
set_target_properties(tcp_client PROPERTIES COMPILE_FLAGS "${OpenRAVE_CXX_FLAGS}")
set_target_properties(tcp_client PROPERTIES LINK_FLAGS "${OpenRAVE_LINK_FLAGS}")
target_link_libraries(tcp_client ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} 
                            ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})
install(TARGETS tcp_client)