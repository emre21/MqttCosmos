#ifndef MQTT_HELPER_FUNCS_HPP
#define MQTT_HELPER_FUNCS_HPP

#include <climits>
#include <cstdint>
#include <optional>

constexpr std::size_t LIMIT_UNIT_REMAINIG = CHAR_MAX + 1;

extern std::optional<std::size_t> CalculateRemaningLenght(uint8_t byte_0);
extern std::optional<std::size_t> CalculateRemaningLenght(uint8_t byte_0, uint8_t byte_1);
extern std::optional<std::size_t> CalculateRemaningLenght(uint8_t byte_0, uint8_t byte_1, uint8_t byte_2);
extern std::optional<std::size_t> CalculateRemaningLenght(uint8_t byte_0, uint8_t byte_1, uint8_t byte_2, uint8_t byte_3);

#endif