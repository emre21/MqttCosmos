
#include "connection.hpp"
#include "mqtt_def.hpp"
#include "mqtt_packet.hpp"
#include <cstdint>
#include <unordered_map>


void InvalidHandler() {}
std::unordered_map<MessageType, std::function<void(void)>> handlers
{
    {MessageType::CONNECT,      InvalidHandler},
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

void Connection::Start() {
    // Todo move to Run Function
    FixedHeader header = ReadFixedHeader();
    if (auto handler = handlers[static_cast<MessageType>(header.messageType)]; handler) {
        handler();
    }
}

FixedHeader ReadFixedHeader() { return FixedHeader{}; }