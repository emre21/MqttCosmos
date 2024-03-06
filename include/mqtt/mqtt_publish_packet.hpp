#ifndef MQTT_PUBLISH_PACKET_HPP
#define MQTT_PUBLISH_PACKET_HPP


#include <span>
#include "mqtt_packet.hpp"

class MqttPublishPacket : public MqttBasePacket {
public:
    const Topic& GetTopic();
    uint16_t GetMessageIdentifier();
    const std::span<uint8_t>& GetMessage();

    void SetPacketData(const std::span<uint8_t>& packetData) override;
    const std::span<uint8_t>& GetPacketData() override; 

private:
    void Parse();
private:
    VariableHeader<MessageType::PUBLISH> variableHeader_;
    Payload<MessageType::PUBLISH> payload_;
};

#endif