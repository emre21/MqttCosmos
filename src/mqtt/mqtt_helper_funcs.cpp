#include "mqtt_helper_funcs.hpp"

std::optional<std::size_t> CalculateRemaningLenght(uint8_t byte_0)
{
    if (byte_0 >= LIMIT_UNIT_REMAINIG ) {
        return std::nullopt;
    }

    return static_cast<std::size_t>(byte_0);
}

std::optional<std::size_t> CalculateRemaningLenght(uint8_t byte_0, uint8_t byte_1)
{
    if (byte_1  >=LIMIT_UNIT_REMAINIG ) {
        return std::nullopt;
    } 
    
    return (LIMIT_UNIT_REMAINIG * static_cast<std::size_t>(byte_1)) + byte_0;
}

std::optional<std::size_t> CalculateRemaningLenght(uint8_t byte_0, uint8_t byte_1, uint8_t byte_2)
{
    if (byte_2 >=LIMIT_UNIT_REMAINIG) {
        return std::nullopt;
    }
    return (static_cast<std::size_t>(byte_2) * LIMIT_UNIT_REMAINIG * LIMIT_UNIT_REMAINIG )
        + (LIMIT_UNIT_REMAINIG * static_cast<std::size_t>(byte_1)) + byte_0;
}

std::optional<std::size_t> CalculateRemaningLenght(uint8_t byte_0, uint8_t byte_1, uint8_t byte_2, uint8_t byte_3)
{
    if (byte_3 >=LIMIT_UNIT_REMAINIG ) {
        return std::nullopt;
    }
    return (static_cast<std::size_t>(byte_3)*LIMIT_UNIT_REMAINIG*LIMIT_UNIT_REMAINIG*LIMIT_UNIT_REMAINIG) 
        +  (static_cast<std::size_t>(byte_2) * LIMIT_UNIT_REMAINIG * LIMIT_UNIT_REMAINIG )
        + (LIMIT_UNIT_REMAINIG * static_cast<std::size_t>(byte_1)) + byte_0;
}