#pragma once
#include <sys/socket.h>
#include <string>
#include <memory>
#include <boost/asio.hpp>

namespace asio = boost::asio;
constexpr size_t SERVER_RECV_BUFF_LEN = 512;
constexpr size_t SERVER_WRITE_BUFF_LEN = 512;

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
    typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
    ~TcpConnection() = default;
    TcpConnection(const TcpConnection&) = delete;
    TcpConnection& operator=(const TcpConnection) = delete;

    static TcpConnectionPtr create(asio::io_context& ioContext);
    asio::ip::tcp::socket& getSocket(){return m_socket;}
    bool start();

private:
    TcpConnection(asio::io_context& ioContext) 
    :   m_socket(ioContext)
    {
        clearOutBuff();
        clearInBuff();
    }
    void writeHandler(const boost::system::error_code& err, size_t byteLen);
    void receiveHandler(const boost::system::error_code& err, size_t byteLen);
    bool prepOutMsg(std::string&& msg);
    bool clearOutBuff();
    bool clearInBuff();
    bool doWrite(std::string&& msg);
    bool doRead();
    bool stop();
    asio::ip::tcp::socket m_socket;
    char m_inBuff[SERVER_RECV_BUFF_LEN];
    char m_outBuff[SERVER_RECV_BUFF_LEN];
};