#pragma once

#include <string>
#include <vector>

using byte = uint8_t;

std::vector<byte> encrypt_xor(const std::string& text, const std::string& key);
std::string       decrypt_xor(std::vector<byte>& encrypted, const std::string& key);

std::vector<byte> read_binary(const std::string& fname);
void              write_binary(const std::vector<byte>& data, const std::string& fname);
