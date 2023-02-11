#include "HttpServer/HttpServer.hpp"

constexpr int MAX_CONNECTION = 10;

HttpServer::HttpServer(std::string ipAddr, int port) : m_ipAddr(ipAddr), m_port(port){


}

HttpServer::~HttpServer(){
    stop();
}

bool HttpServer::setup(){
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(m_socket<0)
    {
        std::cout<<"Cannot_create_socket"<<std::endl;
        return false;
    }
    m_socketAddr.sin_family = AF_INET;
    m_socketAddr.sin_addr.s_addr = inet_addr(m_ipAddr.c_str());
    m_socketAddr.sin_port = htons(m_port);
    m_socketAddrPtr.reset(&m_socketAddr);
    m_socketAddrLenPtr = std::make_shared<size_t>(sizeof(m_socketAddr));
    
    if(bind(m_socket, (sockaddr*)m_socketAddrPtr.get(), *m_socketAddrLenPtr) < 0)
    {
        std::cout<<"Failed_to_bind"<<std::endl;
        return false;
    }
    return true;
}

bool HttpServer::start(){
    if(listen(m_socket, MAX_CONNECTION) < 0){
        std::cout<<"Failed_to_listen"<<std::endl;
        return false;
    }
    return true;
}

bool HttpServer::getConnection(){
    m_connection = accept(m_socket, (sockaddr*)m_socketAddrPtr.get(), (socklen_t*)m_socketAddrLenPtr.get());
    if(m_connection < 0){
        std::cout<<"Failed_to_grab_connection"<<std::endl;
        return false;
    }
    return true;
}

bool HttpServer::stop(){
    close(m_socket);
}

