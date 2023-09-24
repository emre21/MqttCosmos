project(MQTT_COSMOS_TEST)

add_executable(mqtt_cosmos_test mqtt_connect_test.cpp)

target_link_libraries(mqtt_cosmos_test gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(mqtt_cosmos_test)