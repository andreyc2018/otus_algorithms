#include "xorcrypt.h"
#include "key.h"
#include <fstream>
#include <iterator>

std::vector<byte> encrypt_xor(const std::string& text, const std::string& key)
{
    std::vector<byte> encrypted;
    Key               k(key);

    for (size_t i = 0; i < text.size(); ++i) {
        encrypted.push_back(text[i] ^ k.next());
    }

    return encrypted;
}

std::string decrypt_xor(std::vector<byte>& encrypted, const std::string& key)
{
    std::string text;
    Key         k(key);

    for (size_t i = 0; i < encrypted.size(); ++i) {
        text.push_back(encrypted[i] ^ k.next());
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

    return data;
}

void write_binary(const std::vector<byte>& data, const std::string& fname)
{
    std::ofstream file(fname, std::ios::out | std::ios::binary);
    std::copy(data.cbegin(), data.cend(), std::ostream_iterator<byte>(file));
    file.close();
}
