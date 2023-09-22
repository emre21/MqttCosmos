#include "mqtt_connect_packet.hpp"

std::optional<std::u8string> MqttConnectPacket::GetUserName() const
{
    return payload_.userName.data;
}

std::optional<std::u8string> MqttConnectPacket::GetPassword() const
{
    return payload_.password.data;
}

std::optional<std::u8string> MqttConnectPacket::GetMessage() const
{
    return payload_.message.data;
}

std::optional<std::u8string> MqttConnectPacket::GetTopic() const
{
    return payload_.topic.data;
}

std::optional<std::u8string> MqttConnectPacket::GetClientId() const
{
    return payload_.clientID.data;
}

uint16_t MqttConnectPacket::GetKeepAliveTimerSeconds()
{
    return variableHeader_.keepAliveTimer.value();
}

void MqttConnectPacket::SetPacketData(const std::vector<uint8_t> &packetData)
{
    packetData_ = packetData_;
}

const std::vector<uint8_t> &MqttConnectPacket::GetPacketData()
{
    return packetData_;
}

void MqttConnectPacket::Parse()
{
    const auto sizeOfPacket = packetData_.size();
    const auto sizeofVariableHeader = sizeof(variableHeader_);
    std::memcpy(&variableHeader_,packetData_.data(),sizeofVariableHeader);
    payload_.Parse(variableHeader_,packetData_.begin()+sizeofVariableHeader);
}
