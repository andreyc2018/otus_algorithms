#include "xorcrypt.h"
#include "key.h"
#include <gtest/gtest.h>

TEST(XorCryptKey, Init)
{
    Key k("");
    EXPECT_EQ('\0', k.next());
}
