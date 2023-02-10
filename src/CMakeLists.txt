add_executable(main main.cpp)

target_link_libraries(main http_server)
install(TARGETS main)


add_subdirectory(HttpServer)