#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <memory>
#include <thread>
#include <chrono>

#include <boost/asio.hpp>
#include <spdlog/spdlog.h>

#include "mqtt_def.hpp"
#include "mqtt_packet.hpp"
#include "mqtt_connect_packet.hpp"

namespace io = boost::asio;
using tcp = io::ip::tcp;

class Connection {
    
public:
    using pointer = std::shared_ptr<Connection>;
    static pointer Create(tcp::socket&& socket) {
        return std::shared_ptr<Connection>(new Connection(std::move(socket)));
    }

    tcp::socket& GetSocket() { return sock_; }
    void SetClientID(const std::u8string& clientID) { clientID_ = clientID; }
    void SetUserName(const std::u8string& userName) { userName_ = userName; }
    void SetPassword(const std::u8string& password) { password_ = password; }
    std::u8string GetClientId() const { return clientID_; }
    void Start();
    void CloseConnection() { sock_.close(); }
    void StartKeepAliveTimer(uint16_t second) { 
        io::steady_timer timer(sock_.get_executor(),std::chrono::seconds(second)); 
        timer.async_wait([&](const boost::system::error_code&) {
            CloseConnection();
        });
    }
private:
    Connection(tcp::socket&& socket)
        : sock_(std::move(socket))
    {
        
    }
private:
    tcp::socket sock_;
    FixedHeader ReadFixedHeader();

    std::u8string clientID_;
    std::u8string userName_;
    std::u8string password_;

};

#endif