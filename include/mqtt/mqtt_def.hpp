#ifndef MQTT_DEF_H
#define MQTT_DEF_H

#include "../topic.hpp"
#include "mqtt_helper_funcs.hpp"
#include <boost/endian.hpp>
#include <cstdint>
#include <iostream>
#include <optional>
#include <span>
#include <vector>

constexpr auto SIZE_OF_BUINT16 = sizeof(boost::endian::big_uint16_t);
constexpr auto SIZE_OF_UINT8 = sizeof(uint8_t);
enum class MessageType : uint8_t
{
    RESERVED_START = 0,
    CONNECT,
    CONNACK,
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

template <MessageType Type> struct VariableHeader
{
};

template <> struct VariableHeader<MessageType::CONNECT>
{
    boost::endian::big_uint16_t sizeOfProtocolName; // delete for mosquitto and paho libraries
    char protocolName[6];
    uint8_t protocolVersion;
    union ConnectFlags {
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
    } ConnectFlags;
    boost::endian::big_uint16_t keepAliveTimer;
};

// Variable Headers

template <> struct VariableHeader<MessageType::CONNACK>
{
    uint8_t reserved;
    uint8_t returnCode;
};

template <> struct VariableHeader<MessageType::PUBLISH>
{
    boost::endian::big_uint16_t topicSize;
    Topic topic;
    boost::endian::big_uint16_t messageIdentifier; // it can be optional
    std::size_t payloadStartPos;

    void Parse(const FixedHeader &fixedHeader, std::span<uint8_t> &buffer)
    {
        std::memcpy(&topicSize, buffer.data(), SIZE_OF_BUINT16);
        std::span<uint8_t>::iterator topicStartPos = buffer.begin() + SIZE_OF_BUINT16;
        auto topicLength = (topicSize.data()[0] << 8) | (topicSize.data()[1] << 0);
        std::span<uint8_t>::iterator topicEndPos = topicStartPos + topicLength;
        std::span<uint8_t> bufferRef(topicStartPos, topicEndPos);
        topic.FromSpan(bufferRef);
        if (fixedHeader.qosLevel == 1 || fixedHeader.qosLevel == 2)
        {
            std::memcpy(&messageIdentifier, topicEndPos._Mybegin, SIZE_OF_BUINT16);
            payloadStartPos = SIZE_OF_BUINT16 + topicLength + SIZE_OF_BUINT16;
        }
        else
        {
            payloadStartPos = SIZE_OF_BUINT16 + topicLength;
        }
    }
};

template <> struct VariableHeader<MessageType::PUBACK>
{
    boost::endian::big_uint16_t messageIdentifier;
};
template <> struct VariableHeader<MessageType::PUBREC>
{
    boost::endian::big_uint16_t messageIdentifier;
};
template <> struct VariableHeader<MessageType::PUBREL>
{
    boost::endian::big_uint16_t messageIdentifier;
};
template <> struct VariableHeader<MessageType::PUBCOMP>
{
    boost::endian::big_uint16_t messageIdentifier;
};
template <> struct VariableHeader<MessageType::SUBSCRIBE>
{
    boost::endian::big_uint16_t messageIdentifier;
};
template <> struct VariableHeader<MessageType::UNSUBSCRIBE>
{
    boost::endian::big_uint16_t messageIdentifier;
};
template <> struct VariableHeader<MessageType::UNSUBACK>
{
    boost::endian::big_uint16_t messageIdentifier;
};

template <> struct VariableHeader<MessageType::SUBACK>
{
    boost::endian::big_uint16_t messageIdentifier;
};

// Payloads
template <MessageType Type> struct Payload
{
};

template <> struct Payload<MessageType::CONNECT>
{
    struct ConnectPayloadDataUnit
    {
        boost::endian::big_uint16_t dataSizeDescriptor = 0;
        std::optional<std::u8string> data = std::nullopt;
        void Parse(const std::span<uint8_t>::iterator &begin)
        {
            std::memcpy(&dataSizeDescriptor, begin._Myptr, SIZE_OF_BUINT16);
            if (ConverToUint16(dataSizeDescriptor) == 0)
            {
                data = std::nullopt;
            }
            std::cout << '\n' << "Data size desc :" << ConverToUint16(dataSizeDescriptor) << '\n';
            data.emplace(begin + SIZE_OF_BUINT16, begin + SIZE_OF_BUINT16 + ConverToUint16(dataSizeDescriptor));
            if (data.has_value())
            {
                printf("%s", (const char *)data.value().c_str());
            }
            else
            {
                printf("EMRE CANNOT CREATE CLIENT ID");
            }
        }
    };

    ConnectPayloadDataUnit clientID;
    ConnectPayloadDataUnit topic;
    ConnectPayloadDataUnit message;
    ConnectPayloadDataUnit userName;
    ConnectPayloadDataUnit password;

    void Parse(const VariableHeader<MessageType::CONNECT> &variableHeader, const std::span<uint8_t> &payloadData)
    {
        auto clientID_it = payloadData.begin();
        std::cout << "Dataszie desc calclualte  :: " << payloadData[1] + ((uint16_t)payloadData[0] << 8);
        clientID.Parse(clientID_it);

        auto topic_it = clientID_it;
        if (variableHeader.ConnectFlags.Bits.willFlag)
        {
            topic_it = clientID_it + ConverToUint16(clientID.dataSizeDescriptor) + SIZE_OF_BUINT16;
            topic.Parse(topic_it);
        }

        auto message_it = topic_it;
        auto hasMessage = variableHeader.ConnectFlags.Bits.willFlag && variableHeader.ConnectFlags.Bits.willQos &&
                          !variableHeader.ConnectFlags.Bits.willRetain;
        if (hasMessage)
        {
            message_it = topic_it + ConverToUint16(topic.dataSizeDescriptor) + SIZE_OF_BUINT16;
            message.Parse(message_it);
        }

        auto userName_it = message_it;
        if (variableHeader.ConnectFlags.Bits.userNameFlag)
        {
            userName_it = message_it + ConverToUint16(message.dataSizeDescriptor) + SIZE_OF_BUINT16;
            userName.Parse(userName_it);
        }

        auto password_it = userName_it;
        if (variableHeader.ConnectFlags.Bits.passwordFlag)
        {
            password_it = userName_it + ConverToUint16(userName.dataSizeDescriptor) + SIZE_OF_BUINT16;
            password.Parse(password_it);
        }
    }
};

template <> struct Payload<MessageType::SUBSCRIBE>
{
  public:
    struct SubscribeDataUnit
    {
        uint16_t topicLength;
        Topic topic;
        uint8_t requestedQos;
    };
    uint16_t filterLSB = 0x00FF;
    uint16_t filterMSB = 0xFF00;

    uint16_t Convert2littleEndian(uint16_t bigEndian) {
        return ((bigEndian & filterMSB) >> 8) | ((bigEndian & filterLSB) << 8);
    }

    void Parse(std::span<uint8_t> &buffer)
    {
        using buffer_iterator = std::span<uint8_t>::iterator;

        auto UnitParser = [&](buffer_iterator begin, uint16_t topicLength) -> SubscribeDataUnit {
            auto beginTopic = begin;
            auto endTopic = beginTopic +  topicLength;
            auto requestedQos = *(endTopic + SIZE_OF_UINT8);
            std::span<uint8_t> topic(beginTopic, endTopic);
            return SubscribeDataUnit{topicLength, Topic(topic), requestedQos};
        };

        auto begin = buffer.begin();
        for (std::size_t i = 0; i < buffer.size();)
        {
            uint16_t topicLenght = (buffer[i] << 8) | buffer[i + 1];
            auto beginTopic = begin+2;
            auto endTopic = beginTopic + topicLenght;
            auto requestedQos = *(endTopic + SIZE_OF_UINT8);
            std::span<uint8_t> topic(beginTopic, topicLenght);
            payloadData.push_back(SubscribeDataUnit{topicLenght,topic,requestedQos});
            i += SIZE_OF_BUINT16 + topicLenght + SIZE_OF_UINT8;
        }
    }

  public:
    std::vector<SubscribeDataUnit> payloadData;
};

template <> struct Payload<MessageType::UNSUBSCRIBE> {
public:
    struct SubscribeDataUnit
    {
        uint16_t topicLength;
        Topic topic;
        uint8_t requestedQos;
    };
    uint16_t filterLSB = 0x00FF;
    uint16_t filterMSB = 0xFF00;

    uint16_t Convert2littleEndian(uint16_t bigEndian) {
        return ((bigEndian & filterMSB) >> 8) | ((bigEndian & filterLSB) << 8);
    }

    void Parse(std::span<uint8_t>& buffer)
    {
        using buffer_iterator = std::span<uint8_t>::iterator;

        auto UnitParser = [&](buffer_iterator begin, uint16_t topicLength) -> SubscribeDataUnit {
            auto beginTopic = begin;
            auto endTopic = beginTopic + topicLength;
            auto requestedQos = *(endTopic + SIZE_OF_UINT8);
            std::span<uint8_t> topic(beginTopic, endTopic);
            return SubscribeDataUnit{ topicLength, Topic(topic), requestedQos };
            };

        auto begin = buffer.begin();
        for (std::size_t i = 0; i < buffer.size();)
        {
            uint16_t topicLenght = (buffer[i] << 8) | buffer[i + 1];
            auto beginTopic = begin + 2;
            auto endTopic = beginTopic + topicLenght;
            auto requestedQos = *(endTopic + SIZE_OF_UINT8);
            std::span<uint8_t> topic(beginTopic, topicLenght);
            payloadData.push_back(SubscribeDataUnit{ topicLenght,topic,requestedQos });
            i += SIZE_OF_BUINT16 + topicLenght + SIZE_OF_UINT8;
        }
    }

public:
    std::vector<SubscribeDataUnit> payloadData;
};

template <> struct Payload<MessageType::SUBACK>
{
    uint8_t qosLevel;
};

template <> struct Payload<MessageType::PUBLISH>
{
    std::span<uint8_t> message;
};

#endif
