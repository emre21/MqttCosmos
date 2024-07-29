#ifndef MQTT_CONNACT_PACKET_HPP
#define MQTT_CONNACT_PACKET_HPP

#include <cstdint>
#include <mqtt_def.hpp>

enum class ConnackResponse : uint8_t {
	CONNECTION_ACCEPTED				= 0,
	UNACCEPTABLE_PROTOCOL_VERSION	= 1,
	IDENTIFIER_REJECTED				= 2,
	SERVER_UNAVAIBLE				= 3,
	BAD_USER_NAME_OR_PASSSWORD		= 4,
	NOT_AUTHORIZED					= 5,
};

class MqttConnackPacket {
public:
	MqttConnackPacket(ConnackResponse response);
	std::vector<uint8_t> ToVector() const;
private:
	FixedHeader fixedHeader_{
		.retain = 0,
		.qosLevel = 0,
		.dupFlag = 0,
		.messageType = 2,
		.remainingLength = 2
	};
	VariableHeader<MessageType::CONNACK> variableHeader_{};
};

#endif