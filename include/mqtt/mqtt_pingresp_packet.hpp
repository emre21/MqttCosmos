
#include "mqtt_def.hpp"
#include "mqtt_packet.hpp"

class MqttPingRespPacket {
public:
	MqttPingRespPacket() = default;
	std::vector<uint8_t> ToVector() {
		return std::vector<uint8_t>{*(uint8_t*)&fixedHeader_, * (uint8_t*)(&fixedHeader_) + 1};
	}
private:
	FixedHeader fixedHeader_{
		.messageType = 13,
	};
};