#ifndef TOPIC_H
#define TOPIC_H

#include <vector>
#include <string>
#include <span>
class Topic{
public:
    Topic() = default; 
    Topic(const std::size_t& topicSize,std::vector<uint8_t>::iterator begin,
        std::vector<uint8_t>::iterator end) 
    {
        FromVector(topicSize,begin,end);
    }
    Topic(const std::size_t& topicSize,std::span<uint8_t>::iterator begin,
        std::span<uint8_t>::iterator end) 
    {
        FromVector(topicSize,begin,end);
    }
    virtual ~Topic() = default;

    void FromVector(const std::size_t& topicSize,std::vector<uint8_t>::const_iterator begin,
        std::vector<uint8_t>::const_iterator end) 
    {
        topic_name.reserve(topicSize);
        std::copy(begin,end,topic_name);
    }
    void FromVector(const std::size_t& topicSize,std::span<uint8_t>::iterator begin,
        std::span<uint8_t>::iterator end) 
    {
        topic_name.reserve(topicSize);
        std::copy(begin,end,topic_name);
    }
    const std::u8string& GetTopicName() {return topic_name;}
private:
    std::u8string topic_name;
};

#endif