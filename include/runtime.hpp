#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include <unordered_map>
#include <unordered_set>

#include "topic.hpp"
#include "connection.hpp"

class Runtime{
public:
    static Runtime& GetInstance() {
        if (!instance_) {
            instance_ = new Runtime;
        }
        return instance_;
    }

private:
    Runtime() = default;
    inline static Runtime* instance_ = nullptr;

    std::unordered_map<Topic,std::vector<Connection::pointer>> subscribers_;
}

#endif