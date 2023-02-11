#include "sys/sys.hpp"

namespace sys{

    namespace detail{
        std::unique_ptr<asio::thread_pool> poolPtr;
        std::unique_ptr<asio::io_context> ioPtr;
    }

    void setup(){
        detail::poolPtr = std::make_unique<asio::thread_pool>(std::thread::hardware_concurrency());
        detail::ioPtr = std::make_unique<asio::io_context>();
    }

    asio::thread_pool& getThreadPool(){
        if( detail::poolPtr ){
            return *detail::poolPtr;
        }
        else
            throw std::logic_error("cannot find thread pool, missing system setup");
    }

    asio::io_context& getIoContext(){
        if(detail::ioPtr){
            return *detail::ioPtr;
        }
        else
            throw std::logic_error("cannot find io context, missing system setup");
    }

    void run(){
        asio::post(getThreadPool(), 
        [&](){
            getIoContext().run();
        });
        getThreadPool().join();
        detail::ioPtr.release();
        detail::poolPtr.release();
    }
}