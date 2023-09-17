cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 20)
set(PROJ_NAME "MqttCosmos")
set(MQTT_COSMOS_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(MQTT_COSMOS_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(MQTT_COSMOS_SRC 
    ${MQTT_COSMOS_SRC_DIR}/main.cpp
    ${MQTT_COSMOS_SRC_DIR}/connection.cpp
)


project({PROJ_NAME})

find_package(Boost REQUIRED)
find_package(spdlog REQUIRED)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${MQTT_COSMOS_INC_DIR}
)


add_executable(${PROJ_NAME} ${MQTT_COSMOS_SRC})
target_link_libraries(${PROJ_NAME} ${Boost_LIBRARY_DIR} spdlog::spdlog)


