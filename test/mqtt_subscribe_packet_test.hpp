#include <cstdint>
#include <vector>
#include <gtest/gtest.h>
#include "mqtt_subscribe_packet.hpp"
#include "mqtt_helper_funcs.hpp"


std::vector<uint8_t> packet_data = {
	0x82,0x10,0x00,0x01,0x00,0x01,0x61,0x00
};

TEST(SUBSCRIBE_PACKET_PARSE, TEST_1) {
	FixedHeader fixedHeader;
	std::memcpy(&fixedHeader, packet_data.data(), sizeof(fixedHeader));
	auto remainingLength = CalculateRemaningLenght(fixedHeader.remainingLength);
	EXPECT_TRUE(remainingLength.has_value() == true);
	EXPECT_TRUE(remainingLength.value() < packet_data.size() - 2);
	std::span<uint8_t> sucbsribeData{ packet_data.begin() + 2,packet_data.end()};
	MqttSubscribePacket packet(fixedHeader, sucbsribeData);
	packet.GetRemainingLenght
	

}