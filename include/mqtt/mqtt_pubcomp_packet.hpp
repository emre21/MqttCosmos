#ifndef MQTT_PUBCOMP_PACKET_HPP
#define MQTT_PUBCOMP_PACKET_HPP

#include "mqtt_def.hpp"
class MqttPubComp {
public:
public:
	MqttPubComp(uint16_t messageId);
	MqttPubComp(uint8_t msb, uint8_t lsb);
	std::vector<uint8_t> ToVector() const;
private:
	FixedHeader fixedHeader_{
		.messageType = 7,
		.remainingLength = 2
	};
	VariableHeader<MessageType::PUBCOMP> variableHeader_;
};
#endif // !MQTT_PUBCOMP_PACKET_HPP
