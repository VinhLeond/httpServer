#pragma once
#include <thread>
#include <boost/asio.hpp>
#include <memory>
#include <iostream>

namespace asio = boost::asio;
namespace sys
{
    asio::thread_pool& getThreadPool();
    asio::io_context& getIoContext();
    void setup();
    void run();
} // namespace sys
