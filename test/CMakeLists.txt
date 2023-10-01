project(MQTT_COSMOS_TEST)



add_executable(mqtt_cosmos_test
"${CMAKE_CURRENT_SOURCE_DIR}/../include/mqtt/mqtt_helper_funcs.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/../include/mqtt/mqtt_packet.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/../src/mqtt/mqtt_helper_funcs.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/../include/mqtt/mqtt_connect_packet.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/../src/mqtt/mqtt_connect_packet.cpp"

mqtt_connect_test.cpp
topic_test.cpp
calculate_remaining_lenght_test.cpp
)

target_link_libraries(mqtt_cosmos_test gtest gtest_main spdlog::spdlog)

include(GoogleTest)
gtest_discover_tests(mqtt_cosmos_test)