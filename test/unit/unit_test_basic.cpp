#include "HttpServer/HttpServer.hpp"
#include "sys/sys.hpp"
#include "catch2/catch_all.hpp"


TEST_CASE(" 1) Server initialization")
{
    sys::setup();
    HttpServer server(sys::getIoContext(), 9000);
    server.start();
}