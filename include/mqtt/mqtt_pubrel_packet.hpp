#ifndef MQTT_PUBREL_PACKET_HPP
#define MQTT_PUBREL_PACKET_HPP

#include <mqtt/mqtt_def.hpp>
#include <mqtt/mqtt_packet.hpp>

class MqttPubRelPacket : public MqttBasePacket {
public:
    void SetPacketData(const std::span<uint8_t>& packetData) override;
    const std::span<uint8_t>& GetPacketData() override;
private:
	VariableHeader<MessageType::PUBREL> variableHeader_;
    void Parse() override;
};
#endif // !MQTT_PUBREL_PACKET_HPP
