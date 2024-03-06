#ifndef MQTT_PACKET_HPP
#define MQTT_PACKET_HPP

#include "mqtt_def.hpp"
#include <cstdint>
#include <optional>
#include <span>


class MqttBasePacket
{
  public:
    MqttBasePacket(FixedHeader fixedHeader, std::span<uint8_t> &packetData)
        : fixedHeader_(fixedHeader), packetData_(packetData)
    {
    }
    const FixedHeader &GetFixedHeader()
    {
        return fixedHeader_;
    }
    void SetFixedHeader(const FixedHeader &fixedHeader)
    {
        fixedHeader_ = fixedHeader;
    }
    void SetRemainingLenght(std::size_t remainingLength)
    {
        remainingLenght_ = remainingLength;
    }
    std::size_t GetRemainingLenght() const
    {
        return remainingLenght_;
    }

    virtual void SetPacketData(const std::span<uint8_t> &packetData) = 0;
    virtual const std::span<uint8_t> &GetPacketData() = 0;

  protected:
    FixedHeader fixedHeader_;
    std::size_t remainingLenght_;
    std::span<uint8_t> &packetData_;

  protected:
    virtual void Parse() = 0;
};

#endif
