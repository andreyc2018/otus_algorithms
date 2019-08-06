#include "key.h"

char Key::next()
{
    if (!key_.empty()) {
        auto i = index_ % key_.size();
        index_++;
        return key_[i];
    }
    return '\0';
}
