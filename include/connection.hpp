#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <memory>
#include <thread>
#include <chrono>

#include <boost/asio.hpp>
#include <spdlog/spdlog.h>
namespace io = boost::asio;
using tcp = io::ip::tcp;

class Connection {
    
public:
    using pointer = std::shared_ptr<Connection>;
    static pointer Create(tcp::socket&& socket) {
        return std::shared_ptr<Connection>(new Connection(std::move(socket)));
    }

    tcp::socket& GetSocket() { return sock_; }

    void Start();

private:
    Connection(tcp::socket&& socket)
        : sock_(std::move(socket))
    {
        
    }
private:
    tcp::socket sock_;
};

#endif