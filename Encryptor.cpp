#include "Encryptor.hpp"
#include "Grid.hpp"
#include <cctype>

using namespace std;

string Encryptor::encrypt(const string& message, int rounds, int gridSize) {
    string result = message;
    for (int i = 0; i < rounds; ++i) {
        int currentSize = (gridSize == 0) ? computeGrid(result) : gridSize;
        result = processEncryption(result, currentSize);
    }
    return result;
}

string Encryptor::processEncryption(const string& message, int gridSize) {
    Grid grid(gridSize);
    grid.fillWithMessage(message);
    grid.fillRandom();
    grid.print();
    return grid.readColumnWise();
}

int Encryptor::computeGrid(const string& message) {
    // Estimate based on number of characters in diamond pattern
    int length = static_cast<int>(message.length());
    int n = 1;
    while ((n * n) < length * 2) n += 2;
    return n;
}
