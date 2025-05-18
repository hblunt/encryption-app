#ifndef DECRYPTOR_HPP
#define DECRYPTOR_HPP

#include <string>

class Decryptor {
public:
    std::string decrypt(const std::string& encryptedMessage, int rounds);

private:
    std::string processDecryption(const std::string& encryptedMessage);
};

#endif
