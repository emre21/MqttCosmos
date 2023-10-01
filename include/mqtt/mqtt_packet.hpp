#ifndef MQTT_PACKET_HPP
#define MQTT_PACKET_HPP

#include <cstdint>
#include <optional>
#include <span>
#include "mqtt_def.hpp"

class MqttBasePacket{
public:
    MqttBasePacket(FixedHeader fixedHeader,const std::span<uint8_t>& packetData)
        : fixedHeader_(fixedHeader) , packetData_(packetData) {}
    const FixedHeader& GetFixedHeader() {return fixedHeader_;}
    void SetFixedHeader(const FixedHeader& fixedHeader) {fixedHeader_ = fixedHeader;}
    void SetRemainingLenght(std::size_t remainingLength) {remainingLenght_ = remainingLength;}
    std::size_t GetRemainingLenght() const {return remainingLenght_;}

    virtual void SetPacketData(const std::span<uint8_t>& packetData) = 0;
    virtual const std::span<uint8_t>& GetPacketData() = 0; 
protected:
    FixedHeader fixedHeader_;
    std::size_t remainingLenght_;
    const std::span<uint8_t>& packetData_;
protected:
    virtual void Parse() = 0;
};


/*
template <MessageType Type>
struct MqttPacket
{
};

template<>
struct MqttPacket<MessageType::CONNECT>
{
    FixedHeader fixedHeader;
    VariableHeader<MessageType::CONNECT> variableHeader;
    Payload<MessageType::CONNECT> payload;
};

template <>
struct MqttPacket<MessageType::CONNACT>
{
    FixedHeader fixedHeader;
    VariableHeader<MessageType::CONNACT> variableHeader;
};


template<>
struct MqttPacket<MessageType::SUBSCRIBE>
{
    FixedHeader fixedHeader;
    VariableHeader<MessageType::SUBSCRIBE> variableHeader;
    Payload<MessageType::SUBSCRIBE> payload;
};


template <>
struct MqttPacket<MessageType::PUBLISH>
{
    FixedHeader fixedHeader;
    VariableHeader<MessageType::PUBLISH> variableHeader;
    Payload<MessageType::PUBLISH> payload;
};
*/
#endif