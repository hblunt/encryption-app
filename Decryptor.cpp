#include "Decryptor.hpp"
#include "Grid.hpp"
#include "HandleException.hpp"

using namespace std;

string Decryptor::decrypt(const string& encryptedMessage, int rounds) {
    string currentProcessingMessage = encryptedMessage;
    for (int i = 0; i < rounds; ++i) {
        bool isFinalRoundForOriginalMessage = (i == rounds - 1);

        // Process decryption for the current round
        try {
            currentProcessingMessage = processDecryption(currentProcessingMessage, isFinalRoundForOriginalMessage);
        }
        catch (const HandleException& e) {
            return e.what();
        }
    }
    return currentProcessingMessage;
}

string Decryptor::processDecryption(const string& encryptedMessage, bool isFinalExtraction) {
    int length = static_cast<int>(encryptedMessage.length());
    int size = 1;
    while (size * size < length) size += 2;
    
    if (length != size * size) {
        throw HandleException("Error: Encrypted message length is not a perfect square.\nPress Enter to continue.");
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
        int expectedLength = static_cast<int>(sqrt(length));
        expectedLength = expectedLength * expectedLength;
        
        if (decryptedMessage.length() > expectedLength) {
            decryptedMessage = decryptedMessage.substr(0, expectedLength);
        }
    }

    return decryptedMessage;
}