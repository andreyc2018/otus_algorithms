#include "key.h"

char Key::next() { return (!key_.empty()) ? key_[index_ % key_.size()] : '\0'; }
