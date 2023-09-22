#ifndef MQTT_SUBSCRIBE_PACKET_HPP
#define MQTT_SUBSCRIBE_PACKET_HPP

#include <cstdint>

#include "mqtt_packet.hpp"
#include "mqtt_def.hpp"
#include "../topic.hpp"


class MqttSubscribePacket : public MqttBasePacket {

public:
    uint16_t GetMessageIdentifier();
    std::vector<std::pair<Topic,uint8_t>> GetSubcribeDatas();
    void SetPacketData(const std::vector<uint8_t>& packetData) override;
    const std::vector<uint8_t>& GetPacketData() override; 
private:
    void Parse() override;
private:
    VariableHeader<MessageType::SUBSCRIBE> variableHeader_;
    Payload<MessageType::SUBSCRIBE> payload_;
};

#endif