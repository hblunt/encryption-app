#include "Decryptor.hpp"
#include "Grid.hpp"

using namespace std;

std::string Decryptor::decrypt(const std::string& encryptedMessage, int rounds) {
    std::string currentProcessingMessage = encryptedMessage;
    for (int i = 0; i < rounds; ++i) {
        bool isFinalRoundForOriginalMessage = (i == rounds - 1); // True if this is the last decryption step overall
        currentProcessingMessage = processDecryption(currentProcessingMessage, isFinalRoundForOriginalMessage);
        
        // Check for error and propagate immediately
        if (currentProcessingMessage.rfind("Error:", 0) == 0) {
            return currentProcessingMessage; 
        }
    }
    return currentProcessingMessage;
}

// Updated signature and call to grid.extractMessage
std::string Decryptor::processDecryption(const std::string& encryptedMessage, bool isFinalExtraction) {
    int length = static_cast<int>(encryptedMessage.length());
    int size = 1;
    while (size * size < length) size += 2;
    
    if (length != size * size) {
        return "Error: Invalid encrypted message length";
    }

    Grid grid(size);

    // Fill the grid column-wise with the encrypted message
    int idx = 0;
    for (int col = 0; col < size; ++col) {
        for (int row = 0; row < size; ++row) {
            if (idx < encryptedMessage.length()) {
                grid.matrix[row][col] = encryptedMessage[idx++];
            }
        }
    }

    // Extract message and limit its length based on the input length
    string decryptedMessage = grid.extractMessage(isFinalExtraction);
    
    // If this is not the final extraction, we need to preserve exact length
    if (!isFinalExtraction) {
        // Calculate how many characters we expect
        int expectedLength = static_cast<int>(sqrt(length)); // Square root of input length
        expectedLength = expectedLength * expectedLength; // Square it to get grid size
        
        // Ensure the message is exactly the right length
        if (decryptedMessage.length() > expectedLength) {
            decryptedMessage = decryptedMessage.substr(0, expectedLength);
        }
    }

    return decryptedMessage;
}