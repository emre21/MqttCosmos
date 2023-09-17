#ifndef MQTT_PACKET_HPP
#define MQTT_PACKET_HPP

#include <cstdint>
#include <optional>
#include "mqtt_def.hpp"

class MqttBasePacket{
public:
    const FixedHeader& GetFixedHeader();
    void SetFixedHeader(const FixedHeader fixedHeader);
    std::optional<std::size_t> CalculateRemaningLenght(uint8_t byte_0,uint8_t byte_1);
    std::optional<std::size_t> CalculateRemaningLenght(uint8_t byte_0,uint8_t byte_1,uint8_t byte_2);
    std::optional<std::size_t> CalculateRemaningLenght(uint8_t byte_0,uint8_t byte_1,uint8_t byte_2,uint8_t byte_3);
    std::size_t GetRemainingLenght() const ;
    
protected:
    FixedHeader fixedHeader_;
    std::size_t remainingLenght
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