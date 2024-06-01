
#include <vector>
#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include "mqtt_publish_packet.hpp"



std::vector<uint8_t> publishData{
	
0x32,
0x0B,

0x00,
0x03,

0x61,
0x2F,
0x62,

0x00,
0x0A,
// payload
'e',
'm',
'r',
'e',
};



TEST(PUBLISH_PACKET_TEST, PARSE) {
	FixedHeader fixedHeader{};
	std::memcpy(&fixedHeader, publishData.data(), sizeof(fixedHeader));
	ASSERT_EQ(fixedHeader.messageType == (int)MessageType::PUBLISH,true);
	auto remainingLength = CalculateRemaningLenght(fixedHeader.remainingLength);
	if (!remainingLength.has_value()) {
		spdlog::error("HAS ERROR FOR CALCULATE REMAINING LENGTH");
	}
	std::span<uint8_t> packetData(publishData.begin() + 2, remainingLength.value());
	MqttPublishPacket packet(fixedHeader, packetData);
	auto messageID = packet.GetMessageIdentifier();
	auto message = packet.GetMessage();
}