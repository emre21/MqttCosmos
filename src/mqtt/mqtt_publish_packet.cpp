#include "mqtt_publish_packet.hpp"

const Topic &MqttPublishPacket::GetTopic()
{
    return variableHeader_.topic;
}

uint16_t MqttPublishPacket::GetMessageIdentifier()
{
    return variableHeader_.messageIdentifier.value();
}

const std::span<uint8_t>& MqttPublishPacket::GetMessage()
{
    return payload_.message;
}

void MqttPublishPacket::SetPacketData(const std::vector<uint8_t>& packetData)
{
    packetData_ = packetData;
}


const std::vector<uint8_t> &MqttPublishPacket::GetPacketData()
{
    return packetData_;
}

void MqttPublishPacket::Parse()
{
    variableHeader_.Parse(GetFixedHeader(),packetData_);
    auto payloadStart = packetData_.begin() + variableHeader_.payloadStartPos;
    payload_.message = std::span<uint8_t>(payloadStart,packetData_.end());
}
