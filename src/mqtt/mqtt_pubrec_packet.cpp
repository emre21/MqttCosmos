#include "mqtt/mqtt_pubrec_packet.hpp"

MqttPubRec::MqttPubRec(uint16_t messageId)
{
	variableHeader_.messageIdentifier = ((messageId << 8 & 0xF0) | (messageId & 0x0F));
}

MqttPubRec::MqttPubRec(uint8_t msb, uint8_t lsb)
{
	variableHeader_.messageIdentifier.data()[0] = msb;
	variableHeader_.messageIdentifier.data()[1] = msb;
}

std::vector<uint8_t> MqttPubRec::ToVector() const
{
	std::vector<uint8_t> returnBuffer(4);
	std::memcpy(returnBuffer.data(), &fixedHeader_, 2);
	std::memcpy(returnBuffer.data() + 2, &variableHeader_, 2);
	return returnBuffer;
}
