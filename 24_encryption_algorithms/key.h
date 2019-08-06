#pragma once

#include <string>

class Key
{
public:
    Key() = delete;
    explicit Key(const std::string& key)
      : key_(key)
    {}

    Key& operator=(const std::string& key)
    {
        reset();
        key_ = key;
        return *this;
    }
    void reset() { index_ = 0; }
    char next();

private:
    std::string key_;
    size_t      index_ = 0;
};
