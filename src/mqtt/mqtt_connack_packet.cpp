#include "mqtt/mqtt_connack_packet.hpp"

namespace 
{
	constexpr auto SIZE_OF_FIXED_HEADER = 2;
	constexpr auto SIZE_OF_VARIABLE_HEADER = 2;
	constexpr auto SIZE_OF_CONNACT_PACKET = 4;
}

MqttConnackPacket::MqttConnackPacket(CONNACK_RESPONSE response) 
{
	variableHeader_.returnCode = static_cast<uint8_t>(response);
}

std::vector<uint8_t> MqttConnackPacket::ToVector() const {
	std::vector<uint8_t> returnBuffer(SIZE_OF_CONNACT_PACKET);
	std::memcpy(returnBuffer.data(), &fixedHeader_, SIZE_OF_FIXED_HEADER);
	std::memcpy(returnBuffer.data() + SIZE_OF_FIXED_HEADER, &variableHeader_, SIZE_OF_VARIABLE_HEADER);
	return returnBuffer;
}