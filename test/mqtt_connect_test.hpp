#include <gtest/gtest.h>
#include <vector>
#include <span>

#include "mqtt_def.hpp"
#include "mqtt_connect_packet.hpp"
#include "topic.hpp"
#include "mqtt_helper_funcs.hpp"

#include <optional>



TEST(MqttPacketTest,Connect) {
        std::vector<uint8_t> connect_packet = {
        // Fixed Header
        0x10,      // CONNECT packet type
        0x17,      // Remaining Length (12 bytes)

        // Variable Header
        0x00,      // Protocol Name Length MSB
        0x06,      // Protocol Name Length LSB
        'M', 'Q', 'I', 's', 'd', 'p',   // Protocol Name: "MQIsdp"
        0x03,      // Protocol Version (3.1)
        0x00,      // Connect Flags (Reserved bits)
        0x3C,      // Keep Alive MSB (60 seconds)
        0x00,      // Keep Alive LSB (60 seconds)

        // Payload
        0x09,      // Client Identifier Length MSB
        0x00,      // Client Identifier Length LSB
        'm', 'y', '_', 'c', 'l', 'i', 'e', 'n', 't'  // Client Identifier: "my_client"
    };
    FixedHeader fixheader;
    std::memcpy(&fixheader,connect_packet.data(),sizeof(fixheader));

    auto x = CalculateRemaningLenght(fixheader.remainingLength);
    std::cout <<connect_packet.size()<<"--"<<x.value();
    ASSERT_EQ(x.value(),connect_packet.size() -2 );
    ASSERT_EQ(fixheader.messageType,static_cast<uint8_t>(MessageType::CONNECT));

    std::span<uint8_t> connect_buffer(connect_packet.begin()+2,connect_packet.end());

    MqttConnectPacket packet(fixheader,connect_buffer);
    ASSERT_EQ(60,packet.GetKeepAliveTimerSeconds());
    ASSERT_TRUE(u8"my_client"==packet.GetClientId().value());
    
    
    
}
