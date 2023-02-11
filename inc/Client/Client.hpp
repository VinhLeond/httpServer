#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

namespace asio = boost::asio;

class TcpClient
{
    public:
    TcpClient(asio::io_context& ioContext);
    bool connect(std::string serverName, std::string serviceName);
    void sendMsg(std::string msg);

    private:
    asio::io_context& m_ioContext;
    std::shared_ptr<asio::ip::tcp::socket> m_socketPtr;
    asio::streambuf m_inputBuff;
    std::string m_outMsg;
    bool m_isStop = false;
    bool startRead();
    void readHandler(const boost::system::error_code& err, size_t byteLen);
    bool startWrite();
    void writeHandler(const boost::system::error_code& err, size_t byteLen);
    void connectHandler(const boost::system::error_code& err, asio::ip::tcp::resolver::iterator endPoitItr);

};