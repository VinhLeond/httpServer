add_executable(main main.cpp)

target_link_libraries(main http_server Threads::Threads)
install(TARGETS main)

add_executable(client client_tester.cpp)

target_link_libraries(client tcp_client Threads::Threads)
install(TARGETS client)


add_executable(server_test main_test.cpp)
target_include_directories(server_test PUBLIC
                                ${OpenRAVE_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/inc)
set_target_properties(server_test PROPERTIES COMPILE_FLAGS "${OpenRAVE_CXX_FLAGS}")
set_target_properties(server_test PROPERTIES LINK_FLAGS "${OpenRAVE_LINK_FLAGS}")
target_link_libraries(server_test ${OpenRAVE_LIBRARIES} ${OpenRAVE_CORE_LIBRARIES} 
                            ${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})

target_link_libraries(server_test Threads::Threads)
install(TARGETS server_test)

add_subdirectory(HttpServer)
add_subdirectory(Client)