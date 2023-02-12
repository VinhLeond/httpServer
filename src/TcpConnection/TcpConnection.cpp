#include "TcpConnection/TcpConnection.hpp"
#include "sys/sys.hpp"

TcpConnection::TcpConnectionPtr TcpConnection::create(asio::io_context& ioContext){
        // return std::make_shared<TcpConnection>(ioContext);
        return TcpConnectionPtr( new TcpConnection(ioContext));
}

bool TcpConnection::start(){
    doWrite("Connected\n");
    doRead();
    // Send Response
    return true;
}

bool TcpConnection::stop(){
    m_socket.close();
    return true;
}

bool TcpConnection::doRead(){
    m_socket.async_receive(asio::buffer(m_inBuff, sizeof(m_inBuff)), 
    [connectionPtr = shared_from_this()](const boost::system::error_code& err, size_t byteLen)
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
        std::string ackMsg = "Server_Receive_data.\n";
        doWrite(std::move(ackMsg));
    }
    else{
        std::cout<<"Failed_to_receive_message: "<<err.message()<<std::endl;
        stop();
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
    else {
		std::cout << "Connection_failed_to_send_message:_" << err.message( )<<std::endl;
        stop();
    }
}

bool TcpConnection::prepOutMsg(std::string&& msg){
    m_outBuff[0]= '\0';
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
        m_outBuff[0]= '\0';
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
        m_inBuff[0]= '\0';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    return true;
}
