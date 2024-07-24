#ifndef MQTT_UNSUBSCRIBE_PACKET_HPP
#define MQTT_UNSUBSCRIBE_PACKET_HPP

#include "mqtt_def.hpp"
#include "mqtt_packet.hpp"
#include <cstdint>

class MqttUnSubscribePacket : public MqttBasePacket {
public:
    MqttUnSubscribePacket(FixedHeader header, std::span<uint8_t>& packetData) : MqttBasePacket(header, packetData) { Parse(); }
    uint16_t GetMessageIdentifier();
    std::vector<std::pair<Topic, uint8_t>> GetUnSubcribeDatas();
    void SetPacketData(const std::span<uint8_t>& packetData) override;
    const std::span<uint8_t>& GetPacketData() override;
private:
    void Parse() override;
private:
	VariableHeader<MessageType::UNSUBSCRIBE> variableHeader_;
	Payload<MessageType::UNSUBSCRIBE> payload_;
};

#endif // !MQTT_UNSUBSCRIBE_PACKET_HPP
