#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include <unordered_map>
#include <unordered_set>

#include "topic.hpp"
#include "connection.hpp"

class Runtime {
public:
    static Runtime& GetInstance() {
        if (!instance_) {
            instance_ = new Runtime;
        }
        return *instance_;
    }
    std::vector<Connection::pointer> GetTopicSubscribers(const Topic& topic);
    bool AddSubscribeToTopic(const Topic& topic, const std::shared_ptr<Connection>& connection);
    bool DeleteSubscriberFromTopic(const Topic& topic, const std::shared_ptr<Connection>& connection);
    bool DeleteSubscriberFromAllTopic(const std::shared_ptr<Connection>& connection);
private:
    Runtime() = default;
    inline static Runtime* instance_ = nullptr;
    // need shared mutex
    //std::unordered_map<Topic, std::vector<Connection::pointer>> subscribers_;
    std::unordered_map<Topic, std::vector<std::shared_ptr<Connection>>> subscribers_;
};

#endif