#include "Encryptor.hpp"
#include "Grid.hpp"
#include <cctype>
#include <iostream>

using namespace std;

string Encryptor::encrypt(const string& message, int rounds, int gridSize) {
    string result = message;
    
    // For first round only, ensure message ends with a period
    if (!result.empty() && result.back() != '.') {
        result += '.';
    }
    
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

    cout << "\nEncrypted grid:\n";
    grid.print();

    return grid.readColumnWise();
}

int Encryptor::computeGrid(const string& message) {
    // Clean the message to estimate properly
    string cleanMessage;
    for (char c : message) {
        if (isalpha(c) || c == '.') {
            cleanMessage += c;
        }
    }
    
    // Estimate based on number of characters in diamond pattern
    int length = static_cast<int>(cleanMessage.length());
    int n = 1;
    while ((n * n) < length * 2) n += 2;
    
    cout << "Computed grid size: " << n << " for message length: " << length << endl;
    return n;
}