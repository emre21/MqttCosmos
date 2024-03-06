#ifndef SERVER_H
#define SERVER_H

#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <optional>
#include <future>
#include "connection.hpp"

namespace io = boost::asio;
using tcp = io::ip::tcp;

class Server : public std::enable_shared_from_this<Server>{
public:
    Server(io::io_context &ctx,tcp::endpoint ep) 
    : ctx_(ctx) 
    , acceptor_(ctx,ep) 
    {
        acceptor_.listen();
    }
    void start() {
        socket_.emplace(ctx_);
        acceptor_.async_accept(*socket_,[this](const boost::system::error_code& ec){
            auto connection = Connection::Create(std::move(*socket_));
            std::thread([connection](){connection->Start();}).detach();
            connections_.push_back(connection);
            start();
        });
        
    }
private:
    io::io_context& ctx_;
    tcp::acceptor acceptor_;
    std::optional<tcp::socket> socket_;
    std::vector<Connection::pointer> connections_;
};

#endif