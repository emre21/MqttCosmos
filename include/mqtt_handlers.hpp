#ifndef MQTT_HANDLERS_HPP
#define MQTT_HANDLERS_HPP

#include "mqtt_def.hpp"
#include "mqtt_packet.hpp"
#include "connection.hpp"

#include <spdlog/spdlog.h>

bool InvalidHandler(const std::shared_ptr<Connection>& connection, const FixedHeader& header) { return false; }

bool ConnectHandler(const std::shared_ptr<Connection>& connection, const FixedHeader& fixedHeader);
bool PublishHandler(const std::shared_ptr<Connection>& connection, const FixedHeader& fixedHeader);
bool SubscribeHandler(const std::shared_ptr<Connection>& connection, const FixedHeader& fixedHeader);
bool UnsubscribeHandler(const std::shared_ptr<Connection>& connection, const FixedHeader& fixedHeader);

std::unordered_map<MessageType, std::function<bool(const std::shared_ptr<Connection>&, const FixedHeader&)>> handlers
{
    {MessageType::CONNECT,      ConnectHandler},
    {MessageType::CONNACK,      InvalidHandler},
    {MessageType::PUBLISH,      InvalidHandler},
    {MessageType::PUBACK,       InvalidHandler},
    {MessageType::PUBREC,       InvalidHandler},
    {MessageType::PUBREL,       InvalidHandler},
    {MessageType::PUBCOMP,      InvalidHandler},
    {MessageType::SUBSCRIBE,    InvalidHandler},
    {MessageType::SUBACK,       InvalidHandler},
    {MessageType::UNSUBSCRIBE,  InvalidHandler},
    {MessageType::UNSUBACK,     InvalidHandler},
    {MessageType::PINGREQ,      InvalidHandler},
    {MessageType::PINGRESP,     InvalidHandler},
    {MessageType::DISCONNECT,   InvalidHandler},
};


#endif