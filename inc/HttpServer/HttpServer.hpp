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
// class HttpServer
// {
//     public:
//     HttpServer()=default;
//     HttpServer(std::string ipAddr, int port);
//     ~HttpServer();
//     bool setup();
//     bool stop();
//     bool start();

//     private:
//     int m_socket;
//     int m_connection;
//     int m_port;
//     std::shared_ptr<size_t> m_socketAddrLenPtr;
//     std::string m_ipAddr;
//     sockaddr_in m_socketAddr;
//     std::shared_ptr<sockaddr_in> m_socketAddrPtr;
//     bool getConnection();
// };

class TcpConnection : public boost::enable_shared_from_this<TcpConnection>
{
public:
    typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
    ~TcpConnection() = default;
    static TcpConnectionPtr create(asio::io_context& ioContext){
        // return std::make_shared<TcpConnection>(ioContext);
        return TcpConnectionPtr( new TcpConnection(ioContext));
    }

    std::shared_ptr<asio::ip::tcp::socket> getSocket(){ return m_socket; }
    
    bool process(std::string&& msg);
private:
    TcpConnection(asio::io_context& ioContext) : m_socket(std::make_shared<asio::ip::tcp::socket>(ioContext)){}
    void writeHandler(const boost::system::error_code& err, size_t byteLen);
    std::shared_ptr<asio::ip::tcp::socket> m_socket;
    std::string m_message;
};

class HttpServer
{
    public:
    HttpServer(asio::io_context& ioContext);
    ~HttpServer();
    bool stop();
    bool start(int portNum);

    private:
    asio::io_context& m_ioContext;
    asio::ip::tcp::acceptor m_acceptor;
    bool startAccept();
    void acceptHandler(const boost::system::error_code& err, TcpConnection::TcpConnectionPtr connection, std::string&& msg);
    void writeHandler(const boost::system::error_code& err, TcpConnection::TcpConnectionPtr connection);
};
