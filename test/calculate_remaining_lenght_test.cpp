#include <gtest/gtest.h>

#include "mqtt_helper_funcs.hpp"


TEST(CalculateRemaningLenght,_1_BYTE_TEST) {
    auto state_1 = CalculateRemaningLenght(127);
    ASSERT_EQ(state_1.value(),127);

    auto state_2 = CalculateRemaningLenght(200);
    //ASSERT_EQ(state_2.value(),std::nullopt);

    auto state_3 = CalculateRemaningLenght(128);
    ASSERT_EQ(state_3.value(),128);

}

