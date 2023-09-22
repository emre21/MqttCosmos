#include "mqtt_subscribe_packet.hpp"
#include <ranges>

uint16_t MqttSubscribePacket::GetMessageIdentifier()
{
    return variableHeader_.messageIdentifier.value();
}


std::vector<std::pair<Topic,uint8_t>> MqttSubscribePacket::GetSubcribeDatas()
{
    std::vector<std::pair<Topic,uint8_t>> datas;
    for (auto& dataUnit : payload_.payloadData) {
        datas.push_back({dataUnit.topic,dataUnit.requestedQos});
    }
    return datas;
}

void MqttSubscribePacket::SetPacketData(const std::vector<uint8_t> &packetData)
{
    packetData_ = packetData;
    Parse();
}

const std::vector<uint8_t> &MqttSubscribePacket::GetPacketData()
{
    return packetData_;
}

void MqttSubscribePacket::Parse()
{
    std::memcpy(&variableHeader_,packetData_.data(),sizeof(variableHeader_));
    std::span<uint8_t> dataRef(packetData_.begin()+2,packetData_.end());
    payload_.Parse(dataRef);
}
