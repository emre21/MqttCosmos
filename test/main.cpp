#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include "calculate_remaining_lenght_test.hpp"
#include "topic_test.hpp"
#include "mqtt_connect_test.hpp"
#include "mqtt_subscribe_packet_test.hpp"
#include "mqtt_publish_packet_test.hpp"
int main(int argc, char* argv[])

{
    ::testing::InitGoogleTest(&argc, argv);
    //spdlog::info("HELOOO MUHAMMED EMRE ALPAR");
    return RUN_ALL_TESTS();
}