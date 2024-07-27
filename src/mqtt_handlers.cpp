
#include "mqtt_handlers.hpp"

#include <spdlog/spdlog.h>

#include "mqtt_connect_packet.hpp"

namespace{

	bool FillConnectionInfos(const std::shared_ptr<Connection>& connection, MqttConnectPacket& connectPacket)
	{
		if (!connectPacket.GetClientId()) {
			spdlog::critical("Client doesnt have clientId");
			return false;
		}
		auto clientID = connectPacket.GetClientId().value();
		connection->SetClientID(clientID);

		connection->SetUserName(connectPacket.GetUserNameFromPacket().value_or(""));
		connection->SetPassword(connectPacket.GetPassword().value_or(""));
		connection->StartKeepAliveTimer(connectPacket.GetKeepAliveTimerSeconds());
		return true;
	}

}

bool ConnectHandler(const std::shared_ptr<Connection>& connection, const FixedHeader& fixedHeader)
{
	if (!connection) {
		spdlog::error("Connect handler connection ptr is null");
		return false;
	}
	
	std::vector<uint8_t> buffer(fixedHeader.remainingLength);
	boost::system::error_code ec;
	connection->GetSocket().read_some(io::mutable_buffer(buffer.data(), fixedHeader.remainingLength), ec);
	std::span<uint8_t> bufferTemp(buffer.begin(), buffer.end());
	MqttConnectPacket connectPacket(fixedHeader,bufferTemp);

	return FillConnectionInfos(connection, connectPacket);;
}
