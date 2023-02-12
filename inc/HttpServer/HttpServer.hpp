#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <memory>
#include <boost/asio.hpp>

#include "TcpConnection/TcpConnection.hpp"

namespace asio = boost::asio;

class HttpServer
{
    public:
    HttpServer(asio::io_context& ioContext, int portNum);
    ~HttpServer();
    bool stop();
    bool start();

    private:
    asio::io_context& m_ioContext;
    asio::ip::tcp::acceptor m_acceptor;
    bool listen();
    void acceptHandler(const boost::system::error_code& err, TcpConnection::TcpConnectionPtr connectionPtr);
    void writeHandler(const boost::system::error_code& err, TcpConnection::TcpConnectionPtr connectionPtr);
};
