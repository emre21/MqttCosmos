#ifndef MQTT_CONNECT_PACKET_HPP
#define MQTT_CONNECT_PACKET_HPP

#include "mqtt_def.hpp"
#include "mqtt_packet.hpp"


class MqttConnectPacket : public MqttBasePacket{
public:
    MqttConnectPacket(FixedHeader header,const std::span<uint8_t>& buffer);
    std::optional<std::u8string> GetUserName() const;
    std::optional<std::u8string> GetPassword() const;
    std::optional<std::u8string> GetMessage() const;
    std::optional<std::u8string> GetTopic() const;
    std::optional<std::u8string> GetClientId() const;
    uint16_t GetKeepAliveTimerSeconds();
    
    void SetPacketData(const std::span<uint8_t>& packetData) override;
    const std::span<uint8_t>& GetPacketData() override; 

private:
    void Parse() override;
private:
    VariableHeader<MessageType::CONNECT> variableHeader_;
    Payload<MessageType::CONNECT> payload_;
};



#endif