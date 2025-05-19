#ifndef DECRYPTOR_HPP
#define DECRYPTOR_HPP

#include <string>

class Decryptor {
public:
    std::string decrypt(const std::string& encryptedMessage, int rounds);
    std::string processDecryption(const std::string& encryptedMessage, bool isFinalExtraction);
private:
    
};

#endif
