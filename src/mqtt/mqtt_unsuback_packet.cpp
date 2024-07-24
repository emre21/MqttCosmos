#include "mqtt_unsuback_packet.hpp"

namespace
{
	constexpr auto SIZE_OF_FIXED_HEADER = 2;
	constexpr auto SIZE_OF_VARIABLE_HEADER = 2;
	constexpr auto SIZE_OF_CONNACT_PACKET = 4;
}

MqttUnSuback::MqttUnSuback(uint16_t messageId)
{
	variableHeader_.messageIdentifier = ((messageId << 8 & 0xF0) | (messageId & 0x0F));
}

MqttUnSuback::MqttUnSuback(uint8_t msb, uint8_t lsb)
{
	variableHeader_.messageIdentifier.data()[0] = msb;
	variableHeader_.messageIdentifier.data()[1] = msb;
}

std::vector<uint8_t> MqttUnSuback::ToVector() const
{
	std::vector<uint8_t> returnBuffer(SIZE_OF_CONNACT_PACKET);
	std::memcpy(returnBuffer.data(), &fixedHeader_, SIZE_OF_FIXED_HEADER);
	std::memcpy(returnBuffer.data() + SIZE_OF_FIXED_HEADER, &variableHeader_, SIZE_OF_VARIABLE_HEADER);
	return returnBuffer;
}
