#include <iostream>
#include <openrave/openrave.h>
#include <HttpServer/HttpServer.hpp>

int main(int argc, char const *argv[])
{
    boost::asio::io_context ioContext;
    HttpServer server(ioContext);
    server.start(303);
    ioContext.run();
    return 0;
}
