#include "HttpServer/HttpServer.hpp"

constexpr int MAX_CONNECTION = 10;

/*
*        
*           TCP_CONNECTION
*
*/
void TcpConnection::writeHandler(const boost::system::error_code& err, size_t writeLen){
	if( !err )
		std::cout << "Connection_fFinished_sending_message\n"<<std::endl;
    else 
		std::cerr << "Connection_failed_to_send_message:_" << err.message( )<<std::endl;

    // asio::post(m_socket->get_executor(), 
    // [this, bufferSize{writeLen}] ()
    // {

    // });
}

bool TcpConnection::process(std::string&& msg){
    // asio::async_write(*m_socket, asio::buffer(std::move(msg)),
    // [this](const boost::system::error_code& err, size_t byteLen)
    // {
    //     return this->writeHandler(err, byteLen);
    // });
    // Read Message


    // Send Response
    return true;
}

/*
*        
*           HttpServer
*
*/
HttpServer::HttpServer(boost::asio::io_context& ioContext) 
: m_acceptor(ioContext), m_ioContext(ioContext){
    
}

HttpServer::~HttpServer(){
    
}

bool HttpServer::start(int portNum){
    auto endPoint = asio::ip::tcp::endpoint(asio::ip::tcp::v4(), portNum);
    m_acceptor.set_option( boost::asio::ip::tcp::acceptor::reuse_address( true ) );
    m_acceptor.open(endPoint.protocol());
    m_acceptor.bind( endPoint );
    m_acceptor.listen();
    startAccept();
    return true;
}

void HttpServer::writeHandler(const boost::system::error_code& err, TcpConnection::TcpConnectionPtr connection){
	if( !err ) 
		std::cout << "Server_finished_sending_message\n"<<std::endl;
    else 
		std::cerr << "Server_failed_to_send_message:_"<<err.message( )<<std::endl;
}

void HttpServer::acceptHandler(const boost::system::error_code& err, TcpConnection::TcpConnectionPtr connection, std::string&& msg){
    if(!err){
        asio::async_write(*connection->getSocket(), asio::buffer("Hellow_World!\n"), [this, connection](const boost::system::error_code& err, size_t byteLen){ this->writeHandler(err, connection); });
        connection->process(std::move(msg));
    }
    startAccept();
}

bool HttpServer::startAccept(){
    TcpConnection::TcpConnectionPtr newCon = TcpConnection::create(m_ioContext);
    std::string msg;
    m_acceptor.async_accept(*newCon->getSocket(),
                    [this, newCon, msg = std::move(msg)](const boost::system::error_code& err) mutable{
                        return this->acceptHandler(err, newCon, std::move(msg));
                    });
    return true;
}