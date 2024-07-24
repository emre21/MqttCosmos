#include "mqtt_unsubscribe_packet.hpp"

uint16_t MqttUnSubscribePacket::GetMessageIdentifier()
{
    return ConverToUint16(variableHeader_.messageIdentifier);
    //return variableHeader_.messageIdentifier.value();
}


std::vector<std::pair<Topic, uint8_t>> MqttUnSubscribePacket::GetUnSubcribeDatas()
{
    std::vector<std::pair<Topic, uint8_t>> datas;
    for (auto& dataUnit : payload_.payloadData) {
        datas.push_back({ dataUnit.topic,dataUnit.requestedQos });
    }
    return datas;
}

void MqttUnSubscribePacket::SetPacketData(const std::span<uint8_t>& packetData)
{
    packetData_ = packetData;
    Parse();
}

const std::span<uint8_t>& MqttUnSubcribePacket::GetPacketData()
{
    return packetData_;
}

void MqttUnSubscribePacket::Parse()
{
    std::memcpy(&variableHeader_, packetData_.data(), sizeof(variableHeader_));
    std::span<uint8_t> dataRef(packetData_.begin() + 2, packetData_.end());
    payload_.Parse(dataRef);
}
