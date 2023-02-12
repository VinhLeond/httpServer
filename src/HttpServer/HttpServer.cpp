#include "HttpServer/HttpServer.hpp"
#include "sys/sys.hpp"

constexpr int MAX_CONNECTION = 10;

HttpServer::HttpServer(boost::asio::io_context& ioContext, int portNum) 
: m_acceptor(ioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), portNum)), m_ioContext(ioContext){
    
}

HttpServer::~HttpServer(){
    stop();
}

bool HttpServer::stop(){
    m_acceptor.close();
    return true;
}

bool HttpServer::start(){
    listen();
    return true;
}

void HttpServer::writeHandler(const boost::system::error_code& err, TcpConnection::TcpConnectionPtr connectionPtr){
	if( !err ) 
		std::cout << "Server_finished_sending_message\n"<<std::endl;
    else 
		std::cout << "Server_failed_to_send_message:_"<<err.message( )<<std::endl;
}

void HttpServer::acceptHandler(const boost::system::error_code& err, TcpConnection::TcpConnectionPtr connectionPtr){
    if(!err){
        std::cout<<"Successfully receive connection"<<std::endl;
        // Expand this to multi thread for supporting multi connection
        asio::post(sys::getThreadPool(), 
            [connectionPtr]()
            {
                connectionPtr->start();
            });
        listen();
    }
    else{
        connectionPtr.reset();
    }
}

bool HttpServer::listen(){
    TcpConnection::TcpConnectionPtr newConPtr = TcpConnection::create(m_ioContext);
    m_acceptor.async_accept(newConPtr->getSocket(),
                    [this, newConPtr](const boost::system::error_code& err) {
                        this->acceptHandler(err, newConPtr);
                    });
    return true;
}