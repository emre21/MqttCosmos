#ifndef MQTT_UNSUBACK_PACKET_HPP
#define MQTT_UNSUBACK_PACKET_HPP

#include <cstdint>
#include "mqtt_def.hpp"

class MqttUnSuback {
public:
	MqttUnSuback(uint16_t messageId);
	MqttUnSuback(uint8_t msb, uint8_t lsb);
	std::vector<uint8_t> ToVector() const;
private:
	FixedHeader fixedHeader_{
		.retain = 0,
		.qosLevel = 0,
		.dupFlag = 0,
		.messageType = 11,
		.remainingLength = 2
	};
	VariableHeader<MessageType::UNSUBACK> variableHeader_;
};
#endif