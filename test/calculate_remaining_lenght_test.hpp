#include <gtest/gtest.h>

#include "mqtt_helper_funcs.hpp"


TEST(CalculateRemaningLenght,_1_BYTE_TEST) {
    auto state_1 = CalculateRemaningLenght(127);
    ASSERT_TRUE(state_1.has_value());
    ASSERT_EQ(state_1.value(), 127);

    auto state_2 = CalculateRemaningLenght(200);
    ASSERT_FALSE(state_2.has_value()); // Check that it doesn't have a value

    //auto state_3 = CalculateRemaningLenght(128);
    //ASSERT_TRUE(state_3.has_value());
    //ASSERT_EQ(state_3.value(), 128);
}

/*
TEST(CalculateRemaningLenght,_2_BYTE_TEST) {
    auto state_1 = CalculateRemaningLenght(129,2);
    //ASSERT_EQ(state_1.value(),127);

    auto state_2 = CalculateRemaningLenght(129,129);
    //ASSERT_EQ(state_2.value(),std::nullopt);

    auto state_3 = CalculateRemaningLenght(128,128);
    //ASSERT_EQ(state_3.value(),128);

}
*/