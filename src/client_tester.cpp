#include <iostream>
#include <Client/Client.hpp>

int main(int argc, char const *argv[])
{
    boost::asio::io_context ioContext;
    TcpClient client(ioContext);
    client.connect(argv[1], "daytime");
    ioContext.run();
    return 0;
}
