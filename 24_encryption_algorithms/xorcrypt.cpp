#include "xorcrypt.h"
#include "key.h"
#include <fstream>

std::vector<byte> encrypt_xor(const std::string& text, const std::string& key)
{
    std::vector<byte> encrypted;
    Key               k(key);

    for (size_t i = 0; i < text.size(); ++i) {
        auto temp_k = k.next();
        auto c      = text[i] ^ temp_k;
        //        printf("0x%02X ^ 0x%02X = 0x%02X\n", text[i], temp_k, c);
        encrypted.push_back(c);
    }

    return encrypted;
}

std::string decrypt_xor(std::vector<byte>& encrypted, const std::string& key)
{
    std::string text;
    Key         k(key);

    for (size_t i = 0; i < encrypted.size(); ++i) {
        auto temp_k = k.next();
        auto c      = encrypted[i] ^ temp_k;
        //        printf("0x%02X ^ 0x%02X = 0x%02X\n", encrypted[i], temp_k, c);
        text.push_back(c);
    }

    return text;
}

std::vector<byte> read_binary(const std::string& fname)
{
    std::ifstream  file(fname, std::ios::in | std::ios::binary);
    std::streampos file_size;
    file.unsetf(std::ios::skipws);

    file.seekg(0, std::ios::end);
    file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<byte> data;
    data.reserve(file_size);

    std::copy(std::istream_iterator<byte>(file), std::istream_iterator<byte>(),
              std::back_inserter(data));

    //    for (size_t i = 0; i < data.size(); ++i) {
    //        printf("0x%02X\n", data[i]);
    //    }

    return data;
}

void write_binary(const std::vector<byte>& data, const std::string& fname)
{
    std::ofstream file(fname, std::ios::out | std::ios::binary);
    //    for (size_t i = 0; i < data.size(); ++i) {
    //        printf("0x%02X\n", data[i]);
    //    }
    std::copy(data.cbegin(), data.cend(), std::ostream_iterator<byte>(file));
    file.close();
}
