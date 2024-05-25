#include <cstdint>
#include <vector>
#include <spdlog/spdlog.h>
#include <gtest/gtest.h>
#include "mqtt_subscribe_packet.hpp"
#include "mqtt_helper_funcs.hpp"


std::vector<uint8_t> packet_data{
                    0x82, // Fixed Header
                    0x0E, // Remaining Length 
                    0x00, // Message ID 1. byte
                    0x0A, // Message ID 2. byte
                    0x00, // Topic Length 1.byte
                    0x03, // Topic Length 2.byte
                    0x61, // a
                    0x2F, // /
                    0x62, // b
                    0x01, // Request Qos (1)
                    0x00, // Topic Length 1.byte
                    0x03, // Topic Length 2.byte
                    0x63, // c
                    0x2F, // /
                    0x64, // d
                    0x02, // Request Qos (2)
};

TEST(SUBSCRIBE_PACKET_PARSE, TEST_1) {
	FixedHeader fixedHeader;
	std::memcpy(&fixedHeader, packet_data.data(), sizeof(fixedHeader));
	auto remainingLength = CalculateRemaningLenght(fixedHeader.remainingLength);
    EXPECT_TRUE(fixedHeader.messageType == static_cast<uint8_t>(MessageType::SUBSCRIBE));
    EXPECT_TRUE(remainingLength.has_value() == true);
    EXPECT_TRUE(remainingLength.value() == packet_data.size() - 2);
    std::span<uint8_t> subscribe_packet_data{ packet_data.begin() + 2,packet_data.end() };
    MqttSubscribePacket subscribe_packet(fixedHeader, subscribe_packet_data);
    auto data = subscribe_packet.GetSubcribeDatas();
    EXPECT_TRUE(data.size() == 2);
}