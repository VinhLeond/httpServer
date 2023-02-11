#include <openrave/openrave.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <memory>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

namespace asio = boost::asio;
constexpr size_t SERVER_RECV_BUFF_LEN = 8192;
constexpr size_t SERVER_WRITE_BUFF_LEN = 8192;

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
    typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
    ~TcpConnection() = default;
    TcpConnection(const TcpConnection&) = delete;
    TcpConnection& operator=(const TcpConnection) = delete;

    static TcpConnectionPtr create(asio::io_context& ioContext){
        // return std::make_shared<TcpConnection>(ioContext);
        return TcpConnectionPtr( new TcpConnection(ioContext));
    }
    asio::ip::tcp::socket& getSocket(){return m_socket;}
    bool start();

private:
    TcpConnection(asio::io_context& ioContext) : m_socket(ioContext)
    {
        memset(m_inBuff, 0, sizeof(m_inBuff));
        memset(m_outBuff, 0, sizeof(m_outBuff));
    }
    void writeHandler(const boost::system::error_code& err, size_t byteLen);
    void receiveHandler(const boost::system::error_code& err, size_t byteLen);
    bool prepOutMsg(std::string&& msg);
    bool clearOutBuff();
    bool clearInBuff();
    bool doWrite(std::string&& msg);
    bool doRead();
    asio::ip::tcp::socket m_socket;
    char m_inBuff[SERVER_RECV_BUFF_LEN];
    char m_outBuff[SERVER_RECV_BUFF_LEN];
    std::string m_message;
};

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
    bool startAccept();
    void acceptHandler(const boost::system::error_code& err, TcpConnection::TcpConnectionPtr connectionPtr, std::string&& msg);
    void writeHandler(const boost::system::error_code& err, TcpConnection::TcpConnectionPtr connectionPtr);
};
