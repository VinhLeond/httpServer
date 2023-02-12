add_executable(main main.cpp)

target_link_libraries(main http_server tcp_connection sys Threads::Threads)
install(TARGETS main)

add_executable(client client_tester.cpp)

target_link_libraries(client tcp_client sys Threads::Threads)
install(TARGETS client)

add_subdirectory(HttpServer)
add_subdirectory(TcpConnection)
add_subdirectory(Client)
add_subdirectory(sys)