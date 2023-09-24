#include <gtest/gtest.h>
#include <vector>
#include <span>

#include "mqtt_def.hpp"
//#include "mqtt_connect_packet.hpp"
#include "topic.hpp"
#include "mqtt_helper_funcs.hpp"
#include <optional>


TEST(MqttPacketTest,Connect) {
        std::vector<uint8_t> connect_packet = {
        // Fixed Header
        0x10,      // CONNECT packet type
        0x0C,      // Remaining Length (12 bytes)

        // Variable Header
        0x00,      // Protocol Name Length MSB
        0x06,      // Protocol Name Length LSB
        'M', 'Q', 'I', 's', 'd', 'p',   // Protocol Name: "MQIsdp"
        0x03,      // Protocol Version (3.1)
        0x00,      // Connect Flags (Reserved bits)
        0x3C,      // Keep Alive MSB (60 seconds)
        0x00,      // Keep Alive LSB (60 seconds)

        // Payload
        0x00,      // Client Identifier Length MSB
        0x08,      // Client Identifier Length LSB
        'm', 'y', '_', 'c', 'l', 'i', 'e', 'n', 't'  // Client Identifier: "my_client"
    };
    FixedHeader fixheader;
    std::memcpy(&fixheader,connect_packet.data(),sizeof(fixheader));  
    auto x = CalculateRemaningLenght(fixheader.remainingLength);
   std::cout << x.value();
    //ASSERT_EQ(x.value(),10);
    ASSERT_EQ(fixheader.messageType,static_cast<uint8_t>(MessageType::CONNECT));
    
}


TEST(TopicTest,init) {
    std::vector<uint8_t> test_data {'e','m','r','e'};
    std::span<uint8_t> test(test_data.begin(),test_data.end());

    Topic t(test);
   // std::cout << t.GetTopicName().size();
    //printf("%s",(const char *)t.GetTopicName().c_str());
    //std::cout << std::string(t.GetTopicName().begin(),t.GetTopicName().end());    
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}