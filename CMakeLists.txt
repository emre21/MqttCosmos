cmake_minimum_required(VERSION 3.15)
set(PROJ_NAME "MqttCosmos")
project({PROJ_NAME})
enable_testing()
include(CTest)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#https://google.github.io/googletest/quickstart-cmake.html
include(FetchContent)
FetchContent_Declare(
        googletest
         URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
#set(BUILD_GTEST ON CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

set(BOOST_ROOT "C:\\Development\\ThirdpartyLibs\\boost_1_83_0")
set(BOOST_INCLUDEDIR "C:\\Development\\ThirdpartyLibs\\boost_1_83_0\\boost")
set(BOOST_LIBRARYDIR "C:\\Development\\ThirdpartyLibs\\boost_1_83_0\\lib64-msvc-14.3")
set(spdlog_DIR "C:\\Development\\ThirdpartyLibs\\spdlog\\build")


set(MQTT_COSMOS_INC_DIRS 
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/mqtt")
set(MQTT_COSMOS_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(MQTT_COSMOS_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/mqtt/mqtt_helper_funcs.hpp
    ${MQTT_COSMOS_SRC_DIR}/main.cpp
    ${MQTT_COSMOS_SRC_DIR}/connection.cpp
    ${MQTT_COSMOS_SRC_DIR}/mqtt/mqtt_helper_funcs.cpp
    ${MQTT_COSMOS_SRC_DIR}/mqtt/mqtt_connect_packet.cpp
    ${MQTT_COSMOS_SRC_DIR}/mqtt/mqtt_subscribe_packet.cpp
    ${MQTT_COSMOS_SRC_DIR}/mqtt/mqtt_publish_packet.cpp
    ${MQTT_COSMOS_SRC_DIR}/mqtt/mqtt_connack_packet.cpp
    ${MQTT_COSMOS_SRC_DIR}/mqtt/mqtt_puback_packet.cpp
    ${MQTT_COSMOS_SRC_DIR}/mqtt/mqtt_pubrec_packet.cpp
    ${MQTT_COSMOS_SRC_DIR}/mqtt/mqtt_pubrel_packet.cpp
    ${MQTT_COSMOS_SRC_DIR}/mqtt/mqtt_pubcomp_packet.cpp
)






find_package(Boost REQUIRED)
if (Boost_FOUND)
    message("Founded boost")
endif()


find_package(spdlog REQUIRED)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${MQTT_COSMOS_INC_DIRS}
)


add_executable(${PROJ_NAME} ${MQTT_COSMOS_INC_DIRS} ${MQTT_COSMOS_SRC})
target_link_libraries(${PROJ_NAME} ${Boost_LIBRARY_DIR} spdlog::spdlog) 
#

add_subdirectory(test)

