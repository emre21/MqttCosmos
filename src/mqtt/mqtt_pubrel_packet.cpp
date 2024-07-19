#include <mqtt/mqtt_pubrel_packet.hpp>

void MqttPubRelPacket::SetPacketData(const std::span<uint8_t>& packetData)
{
	packetData_ = packetData;
	Parse();
}

const std::span<uint8_t>& MqttPubRelPacket::GetPacketData()
{
	return packetData_;
}

void MqttPubRelPacket::Parse()
{
	std::memcpy((void *)&variableHeader_, packetData_.data(), sizeof(variableHeader_));
}
