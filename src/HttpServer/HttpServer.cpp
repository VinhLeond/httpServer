#include "HttpServer/HttpServer.hpp"

constexpr int MAX_CONNECTION = 10;

/********************************************************************************
*        
*           TCP_CONNECTION
*
********************************************************************************/

bool TcpConnection::start(){
    doWrite("Connected\n");
    doRead();
    // Send Response
    return true;
}

bool TcpConnection::doRead(){
    m_socket.async_receive(asio::buffer(m_inBuff, sizeof(m_inBuff)), 
    [connectionPtr = shared_from_this()](boost::system::error_code err, size_t byteLen)
    {
        connectionPtr->receiveHandler(err, byteLen);
    });
    return true;
}

void TcpConnection::receiveHandler(const boost::system::error_code& err, size_t byteLen)
{
    if(!err){
        std::cout<<"Received_Data: "<<m_inBuff<<std::endl;
        // Process package
        clearInBuff();
        doWrite("Acknowledge\n");
    }
    else{
        std::cout<<"Failed_to_receive_message: "<<err.message()<<std::endl;
    }
}


bool TcpConnection::doWrite(std::string&& msg){
    prepOutMsg(std::move(msg));
    asio::async_write(m_socket, asio::buffer(m_outBuff, SERVER_WRITE_BUFF_LEN), 
    [connectionPtr = shared_from_this()](const boost::system::error_code& err, size_t byteLen)
    {
        connectionPtr->writeHandler(err, byteLen);
    });
    return true;
}

void TcpConnection::writeHandler(const boost::system::error_code& err, size_t writeLen){
	if( !err ){
        std::cout << "Sent_Data: " << m_outBuff << std::endl;
        clearOutBuff();

        m_socket.async_receive(asio::buffer(m_inBuff, SERVER_RECV_BUFF_LEN), 
        [connectionPtr = shared_from_this()](const boost::system::error_code& err, size_t byteLen)
        {
            connectionPtr->receiveHandler(err, byteLen);
        });
    }
    else 
		std::cout << "Connection_failed_to_send_message:_" << err.message( )<<std::endl;
}

bool TcpConnection::prepOutMsg(std::string&& msg){
    memset(m_inBuff, 0, sizeof(m_inBuff));
    try
    {
        strcpy(m_outBuff, msg.c_str());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}

bool TcpConnection::clearOutBuff(){
    try
    {
        memset(m_outBuff, 0, sizeof(m_outBuff));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}

bool TcpConnection::clearInBuff(){
    try
    {
        memset(m_inBuff, 0, sizeof(m_inBuff));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}






/********************************************************************************
*
*        
*           HttpServer
*
********************************************************************************/
HttpServer::HttpServer(boost::asio::io_context& ioContext, int portNum) 
: m_acceptor(ioContext, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), portNum)), m_ioContext(ioContext){
    
}

HttpServer::~HttpServer(){
    
}

bool HttpServer::start(){
    startAccept();
    return true;
}

void HttpServer::writeHandler(const boost::system::error_code& err, TcpConnection::TcpConnectionPtr connectionPtr){
	if( !err ) 
		std::cout << "Server_finished_sending_message\n"<<std::endl;
    else 
		std::cout << "Server_failed_to_send_message:_"<<err.message( )<<std::endl;
}

void HttpServer::acceptHandler(const boost::system::error_code& err, TcpConnection::TcpConnectionPtr connectionPtr, std::string&& msg){
    if(!err){
        std::cout<<"Successfully receive connection"<<std::endl;
        // Expand this to multi thread for supporting multi connection
        connectionPtr->start();
        startAccept();
    }
    else
    {
        connectionPtr.reset();
    }
}

bool HttpServer::startAccept(){
    TcpConnection::TcpConnectionPtr newConPtr = TcpConnection::create(m_ioContext);
    m_acceptor.async_accept(newConPtr->getSocket(),
                    [this, conPtr = newConPtr, msg = "Connected"](const boost::system::error_code& err) {
                        std::cout<<"In_Lambda_"<<conPtr.use_count()<<std::endl;
                        this->acceptHandler(err, conPtr, std::move(msg));
                    });
    return true;
}