#include "xorcrypt.h"
#include "key.h"
#include <gtest/gtest.h>

TEST(XorCryptKey, Init)
{
    Key k("");
    EXPECT_EQ('\0', k.next());

    std::string expect = "hello";

    k = expect;
    for (int i = 0; i < 10; ++i) {
        int idx = i % expect.size();
        EXPECT_EQ(expect[idx], k.next());
    }
}

TEST(Encrypt, Decrypt)
{
    char a = 'h';
    char k = 'a';
    byte c = a ^ k;
    printf("0x%X ^ 0x%X = 0x%X\n", a, k, c);
    printf("0x%X ^ 0x%X = 0x%X\n", c, k, c ^ k);
    EXPECT_EQ('h', c ^ k);
}

TEST(Xor, EncryptMsgDecrypt)
{
    std::string key = "strong key";
    std::string msg = "hidden message";

    auto encrypted = encrypt_xor(msg, key);
    auto decrypted = decrypt_xor(encrypted, key);

    EXPECT_EQ(msg, decrypted);
}
