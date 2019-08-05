#include "xorcrypt.h"
#include <string>
#include <fstream>
#include <memory>

int main(int argc, char* argv[])
{
    std::string text            = (argc > 1) ? argv[1] : "hello, world!";
    std::string key             = (argc > 2) ? argv[2] : "algorithms";
    std::string input_fname     = (argc > 3) ? argv[3] : "input.txt";
    std::string encrypted_fname = (argc > 4) ? argv[4] : "encrypted.bin";

    auto encrypted = encrypt_xor(text.c_str(), key.c_str());

    write_binary(encrypted, encrypted_fname);

    std::ofstream file(input_fname);
    file << key << "\n" << text;

    return 0;
}
