#include "topic.hpp"
#include <gtest/gtest.h>
#include <unordered_map>

TEST(topic,init){
    
    std::vector<uint8_t> test_topic = {
        'e','m','r','e'
    };

    std::span<uint8_t> topic_span(test_topic.begin(),test_topic.end());
    Topic t(topic_span);

    auto name = t.GetTopicName();
    
    ASSERT_EQ(name.size(),4);
    std::u8string utf8str = u8"emre";
    ASSERT_TRUE(name == utf8str);

}


TEST(topic,compare) {

    std::vector<uint8_t> test_topic = {
        'e','m','r','e'
    };
    std::vector<uint8_t> test_topic_2 = {
        'a','l','p','a','r'
    };  

    std::span<uint8_t> mockTopicBuf(test_topic.begin(),test_topic.end());
    std::span<uint8_t> mockTopicBuf_2(test_topic_2.begin(),test_topic_2.end());

    Topic t1(mockTopicBuf);
    Topic t2(mockTopicBuf_2);
    std::unordered_map<Topic,int,TopicHasher> mockTopicMap;

    mockTopicMap[t1] = 1;
    mockTopicMap[t2] = 2;


    ASSERT_EQ(mockTopicMap[t1],1);
    ASSERT_EQ(mockTopicMap[t2],2);
    ASSERT_FALSE(mockTopicMap[t2]==1);
    ASSERT_FALSE(mockTopicMap[t1]==2);
}