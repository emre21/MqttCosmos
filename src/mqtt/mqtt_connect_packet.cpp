#include "mqtt_connect_packet.hpp"
#include <boost/endian/conversion.hpp>
#include <iostream>
#include <spdlog/spdlog.h>
MqttConnectPacket::MqttConnectPacket(FixedHeader header, std::span<uint8_t> &buffer)
    : MqttBasePacket(header, buffer)
{
    std::cout << "->" << std::endl;
    for (const auto &i : buffer)
    {
        std::cout << "->" << i;
    }
    std::cout << "->" << std::endl;
    Parse();
}

std::optional<std::u8string> MqttConnectPacket::GetUserNameFromPacket() const
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
    return ConverToUint16(variableHeader_.keepAliveTimer);
}

void MqttConnectPacket::SetPacketData(const std::span<uint8_t> &packetData)
{
    // packetData_ = packetData;
}

const std::span<uint8_t> &MqttConnectPacket::GetPacketData()
{
    return packetData_;
}

void MqttConnectPacket::Parse()
{
    const auto sizeOfPacket = packetData_.size();
    spdlog::info("connect packet size without fixheader {}", sizeOfPacket);
    const auto sizeofVariableHeader = sizeof(variableHeader_);
    spdlog::info("connect packet variable header size {}", sizeofVariableHeader);
    std::memcpy(&variableHeader_, packetData_.data(), sizeofVariableHeader);
    std::cout << "->" << std::endl;
    for (const auto &i : packetData_)
    {
        std::cout << "->" << i;
    }
    std::cout << "->" << std::endl;
    std::cout << "-------+" << std::string(variableHeader_.protocolName) << '\n';
    std::cout << "-------+" << int(variableHeader_.keepAliveTimer.value()) << '\n';

    std::span<uint8_t> payloadBuffer(packetData_.begin() + sizeofVariableHeader, packetData_.end());
    payload_.Parse(variableHeader_, payloadBuffer);
}
