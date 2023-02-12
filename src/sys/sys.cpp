#include "sys/sys.hpp"

namespace sys{

    namespace detail{
        std::unique_ptr<asio::thread_pool> poolPtr;
        std::unique_ptr<asio::io_context> ioPtr;
    } //namespace sys::detail

    void setup(){
        auto numbOfThread =  std::thread::hardware_concurrency();
        std::cout<<"Creating_thread_pool_with:_"<<numbOfThread<<"_threads"<<std::endl;
        detail::poolPtr = std::make_unique<asio::thread_pool>(numbOfThread);
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
} // namespace sys