#ifndef MQTT_PUBACK_PACKET_HPP
#define MQTT_PUBACK_PACKET_HPP

#include <cstdint>
#include "mqtt_def.hpp"

class MqttPuback {
public:
	MqttPuback(uint16_t messageId);
	MqttPuback(uint8_t msb, uint8_t lsb);
	std::vector<uint8_t> ToVector() const;
private:
	FixedHeader fixedHeader_{
		.retain = 0,
		.qosLevel = 0,
		.dupFlag = 0,
		.messageType = 4,
		.remainingLength = 2
	};
	VariableHeader<MessageType::PUBACK> variableHeader_;
};
#endif