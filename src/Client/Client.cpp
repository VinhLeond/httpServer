#include "Client/Client.hpp"



TcpClient::TcpClient(asio::io_context& ioContext) : m_socketPtr(std::make_shared<asio::ip::tcp::socket>(ioContext)), m_ioContext(ioContext){

}

bool TcpClient::startRead(){
    if(m_isStop)
        return true;

    // Start an asynchronous operation to read a newline-delimited message.
    m_socketPtr->async_receive(asio::buffer(m_inputBuff, sizeof(m_inputBuff)),
    [this](const boost::system::error_code& err, size_t byteLen)
    {
        this->readHandler(err, byteLen);
    });
    return true;
}

void TcpClient::readHandler(const boost::system::error_code& err, size_t byteLen){
    if(!err)
    {
        std::cout << "Received:_" << m_inputBuff << "\n";
        m_inputBuff[0]='\0';
        std::cin >> m_outBuff;
        std::cout << "Entered: " << m_outBuff << std::endl;
        startWrite();
    }
    else
    {
        std::cerr<<"Failed_to_receive_message"<<std::endl;
    }
}

bool TcpClient::startWrite(){
    if(m_isStop)
        return true;
    
    asio::async_write(*m_socketPtr, asio::buffer(m_outBuff, sizeof(m_outBuff)),
    [this](const boost::system::error_code& err, size_t byteLen)
    {
        this->writeHandler(err, byteLen);
    });
    return true;
}

void TcpClient::writeHandler(const boost::system::error_code& err, size_t byteLen){
	if( !err )
    {
        m_outBuff[0] = '\0';
		std::cout << "Client_finished_sending_message\n"<<std::endl;
        startRead();
    }
    else 
		std::cerr << "Client_failed_to_send_message:_"<<err.message( )<<std::endl;
    return;
}

void TcpClient::connectHandler(const boost::system::error_code& err, asio::ip::tcp::resolver::iterator endPoitItr)
{
    if (!err)
    {
        std::cin >> m_outBuff;
        std::cout << "Entered: " << m_outBuff << std::endl;
        startWrite();
        startRead();
    } 
    else if (endPoitItr != asio::ip::tcp::resolver::iterator())
    {
        m_socketPtr->close();
        asio::ip::tcp::endpoint endPoint = *endPoitItr;

    m_socketPtr->async_connect(endPoint,
    [this, endPoitItr = ++endPoitItr](const boost::system::error_code& err)
    {
        this->connectHandler(err, endPoitItr);
    });
    }
}

bool TcpClient::connect(std::string serverName, std::string serviceName){
    asio::ip::tcp::resolver resolver(m_ioContext);
    asio::ip::tcp::resolver::query Query(serverName, serviceName);
    auto endPointIterator = resolver.resolve(serverName, serviceName);
    auto endPoint = *endPointIterator;
    m_socketPtr->async_connect(endPoint,
    [this, endPointIterator = ++endPointIterator](const boost::system::error_code& err)
    {
        this->connectHandler(err, endPointIterator);
    });
    return true;
}


