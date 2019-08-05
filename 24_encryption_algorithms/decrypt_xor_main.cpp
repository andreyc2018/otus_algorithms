#include "xorcrypt.h"
#include <string>
#include <fstream>

int main(int argc, char* argv[])
{
    std::string encrypted_fname = (argc > 1) ? argv[1] : "encrypted.bin";
    std::string key             = (argc > 2) ? argv[2] : "algorithms";
    std::string decrypted_fname = (argc > 3) ? argv[3] : "decrypted.txt";

    auto encryped = read_binary(encrypted_fname);
    auto text     = decrypt_xor(encryped, key);

    std::ofstream file(decrypted_fname);
    file << key << "\n" << text;

    return 0;
}
