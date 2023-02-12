#include "HttpServer/HttpServer.hpp"
#include "TcpConnection/TcpConnection.hpp"
#include "sys/sys.hpp"
#include "catch2/catch_all.hpp"


TEST_CASE(" 1) Server initialization without error")
{
    sys::setup();
    HttpServer server(sys::getIoContext(), 9999);
    server.start();
}