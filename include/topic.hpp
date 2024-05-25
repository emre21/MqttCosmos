#ifndef TOPIC_H
#define TOPIC_H

#include <vector>
#include <string>
#include <span>
#include <cstdlib>
class Topic{
public:
    Topic() = default; 
    /*
    Topic(const std::size_t& topicSize,std::vector<uint8_t>::iterator& begin,
        std::vector<uint8_t>::iterator& end) 
    {
        FromVector(begin,end);
    }
    */
    Topic(const std::span<uint8_t>& bufferRef) noexcept 
    {
        FromSpan(bufferRef);
    }
    virtual ~Topic() = default;

    bool operator==(const Topic& other) const {
        return other.topic_name == this->topic_name; 
    }

    void FromVector(const std::vector<uint8_t>::iterator& begin,
        const std::vector<uint8_t>::iterator& end) 
    {
        topic_name.resize(std::distance(begin,end));
        std::copy(begin,end,topic_name.begin());
        
    }
    void FromSpan(const std::span<uint8_t>& bufferRef) 
    {
        topic_name.resize(bufferRef.size());
        std::copy(bufferRef.begin(),bufferRef.end(),topic_name.begin());
    }
    const std::u8string& GetTopicName() const {return topic_name;}
private:
    std::u8string topic_name;
};

struct TopicHasher{
    std::size_t operator()(const Topic& topic) const {
        return std::hash<std::u8string>{}(topic.GetTopicName());
    }
};

#endif