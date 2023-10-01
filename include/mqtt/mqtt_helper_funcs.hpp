#ifndef MQTT_HELPER_FUNCS_HPP
#define MQTT_HELPER_FUNCS_HPP

#include <climits>
#include <cstdint>
#include <optional>

#include <boost/endian.hpp>

constexpr std::size_t LIMIT_UNIT_REMAINIG = CHAR_MAX + 1;

inline uint16_t ConverToUint16(boost::endian::big_uint16_t bigValue) {
    return (bigValue.data()[0]) | 
        (static_cast<uint16_t>(bigValue.data()[1]) << 8);
}

extern std::optional<std::size_t> CalculateRemaningLenght(uint8_t byte_0);
extern std::optional<std::size_t> CalculateRemaningLenght(uint8_t byte_0, uint8_t byte_1);
extern std::optional<std::size_t> CalculateRemaningLenght(uint8_t byte_0, uint8_t byte_1, uint8_t byte_2);
extern std::optional<std::size_t> CalculateRemaningLenght(uint8_t byte_0, uint8_t byte_1, uint8_t byte_2, uint8_t byte_3);

#endif