#include "Decryptor.hpp"
#include "Grid.hpp"

using namespace std;

string Decryptor::decrypt(const string& encryptedMessage, int rounds) {
    string result = encryptedMessage;
    for (int i = 0; i < rounds; ++i) {
        result = processDecryption(result);
    }
    return result;
}

string Decryptor::processDecryption(const string& encryptedMessage) {
    // TODO: Implement grid reconstruction from columns and diamond decoding
    // Determine grid size (must be odd and such that size*size >= encryptedMessage.length())
    int length = static_cast<int>(encryptedMessage.length());
    int size = 1;
    while (size * size < length) size += 2;

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

    // Extract the message from the grid in diamond order
    return grid.extractMessage();
}
