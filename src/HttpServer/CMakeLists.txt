add_library(http_server HttpServer.cpp)
target_include_directories(http_server PUBLIC
                                ${OpenRAVE_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/inc)
set_target_properties(http_server PROPERTIES COMPILE_FLAGS "${OpenRAVE_CXX_FLAGS}")
set_target_properties(http_server PROPERTIES LINK_FLAGS "${OpenRAVE_LINK_FLAGS}")
target_link_libraries(http_server ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} 
                            ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})
install(TARGETS http_server)
