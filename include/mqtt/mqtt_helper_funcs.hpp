#ifndef MQTT_HELPER_FUNC_HPP
#define MQTT_HELPER_FUNC_HPP

#include <climits>
#include <cstdint>
#include <optional>


constexpr std::size_t LIMIT_UNIT_REMAINIG = CHAR_MAX + 1;

std::optional<std::size_t> CalculateRemaningLenght(uint8_t byte_0);
std::optional<std::size_t> CalculateRemaningLenght(uint8_t byte_0, uint8_t byte_1);
std::optional<std::size_t> CalculateRemaningLenght(uint8_t byte_0, uint8_t byte_1, uint8_t byte_2);
std::optional<std::size_t> CalculateRemaningLenght(uint8_t byte_0, uint8_t byte_1, uint8_t byte_2, uint8_t byte_3);



#endif