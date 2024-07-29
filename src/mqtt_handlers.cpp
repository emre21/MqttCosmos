
#include "mqtt_handlers.hpp"

#include <spdlog/spdlog.h>

#include "mqtt_connect_packet.hpp"
#include "mqtt_connack_packet.hpp"
#include "mqtt_publish_packet.hpp"
#include "mqtt_pubrel_packet.hpp"
#include "mqtt_subscribe_packet.hpp"
#include "mqtt_unsubscribe_packet.hpp"

#include "runtime.hpp"

namespace{

	ConnackResponse FillConnectionInfos(const std::shared_ptr<Connection>& connection, MqttConnectPacket& connectPacket)
	{
		if (!connectPacket.GetClientId()) {
			spdlog::critical("Client doesnt have clientId");
			return ConnackResponse::IDENTIFIER_REJECTED;
		}
		auto clientID = connectPacket.GetClientId().value();
		connection->SetClientID(clientID);

		connection->SetUserName(connectPacket.GetUserNameFromPacket().value_or(""));
		connection->SetPassword(connectPacket.GetPassword().value_or(""));
		connection->StartKeepAliveTimer(connectPacket.GetKeepAliveTimerSeconds());
		return ConnackResponse::CONNECTION_ACCEPTED;
	}

	std::span<uint8_t>& ReadPacketData(const std::shared_ptr<Connection>& connection, const FixedHeader& fixedHeader)
	{
		std::vector<uint8_t> buffer(fixedHeader.remainingLength);
		boost::system::error_code ec;
		connection->GetSocket().read_some(io::mutable_buffer(buffer.data(), fixedHeader.remainingLength), ec);
		std::span<uint8_t> bufferTemp(buffer.begin(), buffer.end());
		return bufferTemp;
	}
}

bool ConnectHandler(const std::shared_ptr<Connection>& connection, const FixedHeader& fixedHeader)
{
	if (!connection) {
		spdlog::error("Connect handler connection ptr is null");
		return false;
	}
	auto bufferTemp = ReadPacketData(connection, fixedHeader);
	MqttConnectPacket connectPacket(fixedHeader,bufferTemp);
	auto fillResult = FillConnectionInfos(connection, connectPacket);
	// Generate Connack Packet
	if (fillResult != ConnackResponse::CONNECTION_ACCEPTED) {
		return false;
	}
	MqttConnackPacket responsePacket(fillResult);
	connection->GetSocket().write_some(responsePacket.ToVector());
	return true;
}

bool PublishHandler(const std::shared_ptr<Connection>& connection, const FixedHeader& fixedHeader)
{
	if (!connection) {
		spdlog::error("Connect handler connection ptr is null");
		return false;
	}

	auto bufferTemp = ReadPacketData(connection, fixedHeader);
	
	MqttPublishPacket publishPacket(fixedHeader, bufferTemp);
	auto messageId = publishPacket.GetMessageIdentifier();
	auto topic = publishPacket.GetTopic();
	auto message = publishPacket.GetTopic();

	auto subsVec = Runtime::GetInstance().GetTopicSubscribers(topic);

	for (auto& sub : subsVec) {
		// Notify Subs
	}
}

bool PubrelHandler(const std::shared_ptr<Connection>& connection, const FixedHeader& fixedHeader)
{
	if (!connection) {
		spdlog::error("Connect handler connection ptr is null");
		return false;
	}

	auto bufferTemp = ReadPacketData(connection, fixedHeader);
	MqttPubRelPacket pubRelPacket(fixedHeader, bufferTemp);

	// Genereta PubComp 
	return true;


}

bool SubscribeHandler(const std::shared_ptr<Connection>& connection, const FixedHeader& fixedHeader)
{
	if (!connection) {
		spdlog::error("Connect handler connection ptr is null");
		return false;
	}

	auto bufferTemp = ReadPacketData(connection, fixedHeader);
	MqttSubscribePacket subscribePacket(fixedHeader, bufferTemp);
	auto topicQosVec = subscribePacket.GetSubcribeDatas();
	// need handle qos
	for (const auto& topic_qos : topicQosVec) {
		Runtime::GetInstance().AddSubscribeToTopic(topic_qos.first, connection);
	}

	// create suback
	return true;
}

bool UnsubscribeHandler(const std::shared_ptr<Connection>& connection, const FixedHeader& fixedHeader)
{
	if (!connection) {
		spdlog::error("Connect handler connection ptr is null");
		return false;
	}

	auto bufferTemp = ReadPacketData(connection, fixedHeader);
	MqttUnSubscribePacket unSubscribePacket(fixedHeader, bufferTemp);
	auto topicQosVec = unSubscribePacket.GetUnSubcribeDatas();
	// need handle qos
	for (const auto& topic_qos : topicQosVec) {
		Runtime::GetInstance().DeleteSubscriberFromTopic(topic_qos.first, connection);
	}

	// Create UnsubAck

	return true;
}

bool PingReqHandler(const std::shared_ptr<Connection>& connection, const FixedHeader& fixedHeader)
{
	if (!connection)
	{
		return false;
	}

}


bool DisconnectHandler(const std::shared_ptr<Connection>& connection, const FixedHeader& fixedHeader)
{
	if (!connection)
	{
		return false;
	}

	Runtime::GetInstance().DeleteSubscriberFromAllTopic(connection);
	connection->CloseConnection();

	// Can be change
	connection.~shared_ptr();
	return true;
}
