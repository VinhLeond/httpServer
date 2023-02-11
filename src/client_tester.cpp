#include <iostream>
#include <Client/Client.hpp>
#include <boost/thread.hpp>
int main(int argc, char const *argv[])
{
    boost::asio::io_context ioContext;
    TcpClient client(ioContext);
    client.connect("localhost", "80");
    // client.sendMsg("HELL_WORLD");
    boost::thread clientThread([&ioContext](){ ioContext.run(); });

    clientThread.join();
    return 0;
}