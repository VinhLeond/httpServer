#include "Client/Client.hpp"



TcpClient::TcpClient(asio::io_context& ioContext) : m_socketPtr(std::make_shared<asio::ip::tcp::socket>(ioContext)), m_ioContext(ioContext){

}

bool TcpClient::startRead(){
    if(m_isStop)
        return true;

    // Start an asynchronous operation to read a newline-delimited message.
    asio::async_read_until(*m_socketPtr, m_inputBuff, '\n',
    [this](const boost::system::error_code& err, size_t byteLen)
    {
        this->readHandler(err, byteLen);
    });
    return true;
}

void TcpClient::readHandler(const boost::system::error_code& err, size_t byteLen){
    if(!err)
    {
        // Extract the newline-delimited message from the buffer.
        std::string line;
        std::istream is(&m_inputBuff);
        std::getline(is, line);

        // Empty messages are heartbeats and so ignored.
        if (!line.empty())
        {
        std::cout << "Received:_" << line << "\n";
        }
        startRead();
    }
    else
    {
        std::cerr<<"Failed_to_receive_message"<<std::endl;
    }
}

void TcpClient::sendMsg(std::string msg)
{
    m_outMsg = std::move(msg);
    startWrite();
}

bool TcpClient::startWrite(){
    if(m_isStop)
        return true;
    
    asio::async_write(*m_socketPtr, asio::buffer(m_outMsg),
    [this](const boost::system::error_code& err, size_t byteLen)
    {
        this->writeHandler(err, byteLen);
    });
    return true;
}

void TcpClient::writeHandler(const boost::system::error_code& err, size_t byteLen){
	if( !err ) 
		std::cout << "Client_finished_sending_message\n"<<std::endl;
    else 
		std::cerr << "Client_failed_to_send_message:_"<<err.message( )<<std::endl;
    return;
}

bool TcpClient::connect(std::string serverName, std::string serviceName){
    asio::ip::tcp::resolver resolver(m_ioContext);
    asio::ip::tcp::resolver::results_type endPoint = resolver.resolve(serverName, serviceName);
    asio::connect(*m_socketPtr, endPoint);
    return true;
}


