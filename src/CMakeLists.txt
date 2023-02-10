add_executable(test helloWorld.cpp)
target_include_directories(test PUBLIC
                                ${OpenRAVE_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/inc)
set_target_properties(test PROPERTIES COMPILE_FLAGS "${OpenRAVE_CXX_FLAGS}")
set_target_properties(test PROPERTIES LINK_FLAGS "${OpenRAVE_LINK_FLAGS}")
target_link_libraries(test ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} 
                            ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})
install(TARGETS test)


add_subdirectory(HttpServer)