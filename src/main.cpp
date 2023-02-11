#include <iostream>
#include <openrave/openrave.h>
#include <HttpServer/HttpServer.hpp>
#include "sys/sys.hpp"

int main(int argc, char const *argv[])
{
    sys::setup();
    HttpServer server(sys::getIoContext(), 9000);
    server.start();
    sys::run();
    return 0;
}
