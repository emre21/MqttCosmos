project(MQTT_COSMOS_TEST)
set(CMAKE_CXX_STANDARD 20)

add_executable(mqtt_cosmos_test
"${CMAKE_CURRENT_SOURCE_DIR}/../include/mqtt/mqtt_helper_funcs.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/../include/mqtt/mqtt_packet.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/../src/mqtt/mqtt_helper_funcs.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/../include/mqtt/mqtt_connect_packet.hpp"
"${CMAKE_CURRENT_SOURCE_DIR}/../src/mqtt/mqtt_connect_packet.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/../src/mqtt/mqtt_subscribe_packet.cpp"
"${CMAKE_CURRENT_SOURCE_DIR}/../src/mqtt/mqtt_publish_packet.cpp"

mqtt_connect_test.hpp
mqtt_subscribe_packet_test.hpp
mqtt_publish_packet_test.hpp
topic_test.hpp
calculate_remaining_lenght_test.hpp
 main.cpp)

target_link_libraries(mqtt_cosmos_test 
gtest 
gtest_main 
spdlog::spdlog)

gtest_discover_tests(mqtt_cosmos_test)