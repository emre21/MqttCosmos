#include <iostream>
#include <spdlog/spdlog.h>
#include <boost/asio.hpp>
#include <cstdint>,

#include "server.hpp"

namespace {
	constexpr uint16_t PORT = 12345;
}

int main() {
	spdlog::info("MqttCosmos Start");
	boost::asio::io_context ctx;
	boost::asio::io_service::work idle(ctx);

	spdlog::info("context start");
	
	Server server(ctx, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT));
	spdlog::info("Server init");
	server.start();
	ctx.run();


}