#pragma once
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

namespace asio = boost::asio;
constexpr size_t CLIENT_RECV_BUFF_LEN = 8192;
constexpr size_t CLIENT_WRITE_BUFF_LEN = 8192;
class TcpClient
{
    public:
    TcpClient(asio::io_context& ioContext);
    bool connect(std::string serverName, std::string serviceName);
    void sendMsg(std::string msg);

    private:
    asio::io_context& m_ioContext;
    std::shared_ptr<asio::ip::tcp::socket> m_socketPtr;
    char m_inputBuff[CLIENT_RECV_BUFF_LEN];
    char m_outBuff[CLIENT_WRITE_BUFF_LEN];
    bool m_isStop = false;
    bool startRead();
    void readHandler(const boost::system::error_code& err, size_t byteLen);
    bool startWrite();
    void writeHandler(const boost::system::error_code& err, size_t byteLen);
    void connectHandler(const boost::system::error_code& err, asio::ip::tcp::resolver::iterator endPoitItr);

};