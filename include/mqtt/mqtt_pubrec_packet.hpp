#ifndef MQTT_PUBREC_PACKET_HPP
#define MQTT_PUBREC_PACKET_HPP

#include <cstdint>
#include "mqtt_def.hpp"

class MqttPubRec {
public:
	MqttPubRec(uint16_t messageId);
	MqttPubRec(uint8_t msb, uint8_t lsb);
	std::vector<uint8_t> ToVector() const;
private:
	FixedHeader fixedHeader_{
		.messageType = 5,
		.remainingLength = 2
	};
	VariableHeader<MessageType::PUBREC> variableHeader_;
};

#endif