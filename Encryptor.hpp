#ifndef ENCRYPTOR_HPP
#define ENCRYPTOR_HPP

#include <string>

class Encryptor {
public:
    std::string encrypt(const std::string& message, int rounds, int gridSize = 0);
    std::string processEncryption(const std::string& message, int gridSize);
    int computeGrid(const std::string& message);  // Changed to public for use in UIHandler
};

#endif