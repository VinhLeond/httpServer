add_executable(server_basic_test unit_test_basic.cpp)
target_include_directories(server_basic_test PUBLIC
                                                ${CMAKE_SOURCE_DIR}/inc
                                                ${CMAKE_SOURCE_DIR}/test/unit/)
set_target_properties(server_basic_test PROPERTIES COMPILE_FLAGS "${OpenRAVE_CXX_FLAGS}")
set_target_properties(server_basic_test PROPERTIES LINK_FLAGS "${OpenRAVE_LINK_FLAGS}")
target_link_libraries(server_basic_test ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES}
                                    ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY}
                                    http_server Catch2::Catch2WithMain Threads::Threads)