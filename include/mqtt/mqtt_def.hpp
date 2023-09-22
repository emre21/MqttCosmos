#ifndef MQTT_DEF_H
#define MQTT_DEF_H

#include <cstdint>
#include <optional>
#include <vector>
#include <span>
#include <boost/endian.hpp>

#include "../topic.hpp"

constexpr auto SIZE_OF_BUINT16 = sizeof(boost::endian::big_uint16_t);
constexpr auto SIZE_OF_UINT8 = sizeof(uint8_t);
enum class MessageType : uint8_t
{
    RESERVED_START = 0,
    CONNECT,
    CONNACT,
    PUBLISH,
    PUBACK,
    PUBREC,
    PUBREL,
    PUBCOMP,
    SUBSCRIBE,
    SUBACK,
    UNSUBSCRIBE,
    UNSUBACK,
    PINGREQ,
    PINGRESP,
    DISCONNECT,
    Reserved_END = 15,

};

struct FixedHeader
{
    uint8_t retain : 1;
    uint8_t qosLevel : 2;
    uint8_t dupFlag : 1;
    uint8_t messageType : 4;
    uint8_t remainingLength;
};

template <MessageType Type>
struct VariableHeader
{
};


template <>
struct VariableHeader<MessageType::CONNECT>
{
    boost::endian::big_uint16_t sizeOfProtocolName; // delete for mosquitto and paho libraries
    char protocolName[6];
    uint8_t protocolVersion;
    union ConnectFlags
    {
        uint8_t connectFlags;
        struct connectFlagsBits
        {
            uint8_t reserved : 1;
            uint8_t userNameFlag : 1;
            uint8_t passwordFlag : 1;
            uint8_t willRetain : 1;
            uint8_t willQos : 2;
            uint8_t willFlag : 1;
            uint8_t cleanSession : 1;
        } Bits;
    }ConnectFlags;
    boost::endian::big_uint16_t keepAliveTimer;
};

// Variable Headers

template <>
struct VariableHeader<MessageType::CONNACT>
{
    uint8_t reserved;
    uint8_t returnCode;
};


template <>
struct VariableHeader<MessageType::PUBLISH>
{
    boost::endian::big_uint16_t topicSize;
    Topic topic;
    boost::endian::big_uint16_t messageIdentifier; // it can be optional
    std::size_t payloadStartPos;

void Parse(const FixedHeader& fixedHeader,const std::vector<uint8_t>& buffer) {
        std::memcpy(&topicSize,buffer.data(),SIZE_OF_BUINT16);
        auto topicStartPos = buffer.begin() + SIZE_OF_BUINT16;
        auto topicEndPos = topicStartPos + topicSize.value();
        topic.FromVector(topicSize.value(),topicStartPos,topicEndPos);
        if (fixedHeader.qosLevel == 1 || fixedHeader.qosLevel == 2 ) {
            std::memcpy(&messageIdentifier,topicEndPos.base(),SIZE_OF_BUINT16);
            payloadStartPos = SIZE_OF_BUINT16 + topicSize.value() + SIZE_OF_BUINT16;
        } else {
            payloadStartPos = SIZE_OF_BUINT16 + topicSize.value();
        }
        
    }
    
};

template <>
struct VariableHeader<MessageType::PUBACK>
{
    boost::endian::big_uint16_t messageIdentifier;
};
template <>
struct VariableHeader<MessageType::PUBREC>
{
    boost::endian::big_uint16_t messageIdentifier;
};
template <>
struct VariableHeader<MessageType::PUBREL>
{
    boost::endian::big_uint16_t messageIdentifier;
};
template <>
struct VariableHeader<MessageType::PUBCOMP>
{
    boost::endian::big_uint16_t messageIdentifier;
};
template <>
struct VariableHeader<MessageType::SUBSCRIBE>
{
    boost::endian::big_uint16_t messageIdentifier;
};
template <>
struct VariableHeader<MessageType::UNSUBSCRIBE>
{
    boost::endian::big_uint16_t messageIdentifier;
};
template <>
struct VariableHeader<MessageType::UNSUBACK>
{
    boost::endian::big_uint16_t messageIdentifier;
};

template <>
struct VariableHeader<MessageType::SUBACK>
{
    boost::endian::big_uint16_t messageIdentifier;
};

// Payloads
template <MessageType Type>
struct Payload
{
};

template <>
struct Payload<MessageType::CONNECT>
{
    struct ConnectPayloadDataUnit{
        boost::endian::big_uint16_t dataSizeDescriptor = 0;
        std::optional<std::u8string> data = std::nullopt;
        void Parse(std::vector<uint8_t>::const_iterator begin) {
            std::memcpy(&dataSizeDescriptor,begin.base(),SIZE_OF_BUINT16);
            if (dataSizeDescriptor.value() == 0) {
                data = std::nullopt;
            }
            data.emplace(begin+SIZE_OF_BUINT16,begin+SIZE_OF_BUINT16+dataSizeDescriptor.value());
        }
    };

    ConnectPayloadDataUnit clientID;
    ConnectPayloadDataUnit topic;
    ConnectPayloadDataUnit message;
    ConnectPayloadDataUnit userName;
    ConnectPayloadDataUnit password;

    void Parse(const VariableHeader<MessageType::CONNECT> &variableHeader, const std::vector<uint8_t>::iterator& payloadDataBeginIt)
    {
        auto clientID_it = payloadDataBeginIt; 
        clientID.Parse(clientID_it);
        
        auto topic_it = clientID_it;
        if (variableHeader.ConnectFlags.Bits.willFlag) {
            topic_it = clientID_it + clientID.dataSizeDescriptor.value() + SIZE_OF_BUINT16;
            topic.Parse(topic_it);
        }

        auto message_it = topic_it;
        auto hasMessage = variableHeader.ConnectFlags.Bits.willFlag && 
                            variableHeader.ConnectFlags.Bits.willQos && 
                            !variableHeader.ConnectFlags.Bits.willRetain;
        if (hasMessage) {
            message_it = topic_it + topic.dataSizeDescriptor.value() + SIZE_OF_BUINT16;
            message.Parse(message_it);
        }

        auto userName_it = message_it;
        if (variableHeader.ConnectFlags.Bits.userNameFlag) {
            userName_it = message_it + message.dataSizeDescriptor.value() + SIZE_OF_BUINT16;
            userName.Parse(userName_it);
        }

        auto password_it = userName_it;
        if (variableHeader.ConnectFlags.Bits.passwordFlag) {
            password_it = userName_it + userName.dataSizeDescriptor.value() + SIZE_OF_BUINT16;
            password.Parse(password_it);
        }
    }

};

template <>
struct Payload<MessageType::SUBSCRIBE> {
public:
    struct SubscribeDataUnit{
        boost::endian::big_uint16_t topicLength;
        Topic topic;
        uint8_t requestedQos;
    };

    void Parse(const std::span<uint8_t>& buffer) {
        using buffer_iterator = std::span<uint8_t>::iterator;
        
        auto UnitParser = [](buffer_iterator begin, boost::endian::big_uint16_t topicLength) -> SubscribeDataUnit {
            auto beginTopic = begin ;
            auto endTopic = beginTopic + topicLength.value();
            auto requestedQos = *(endTopic + SIZE_OF_UINT8);
            return SubscribeDataUnit{
                topicLength,
                Topic(topicLength.value(),beginTopic, endTopic),
                requestedQos
            };
        };

        auto begin = buffer.begin();
        for(std::size_t i = 0 ; i < buffer.size();){
            if (i+SIZE_OF_BUINT16 >= buffer.size()) break;
            boost::endian::big_uint16_t topicLenght;
            std::memcpy(&topicLenght,&buffer[i],SIZE_OF_BUINT16);
            payloadData.push_back(UnitParser(begin,topicLenght));
            i += SIZE_OF_BUINT16 + topicLenght.value() + SIZE_OF_UINT8;
        }

    }

public:
    std::vector<SubscribeDataUnit> payloadData;

};

template <>
struct Payload<MessageType::SUBACK> {
    uint8_t qosLevel;
};

template <>
struct Payload<MessageType::PUBLISH> {
    std::span<uint8_t> message;
};

#endif