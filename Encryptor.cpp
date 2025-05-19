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
    
    // First clean the message (remove spaces, convert to uppercase)
    string cleanMessage;
    for (char c : message) {
        if (isalpha(c) || c == '.') {
            cleanMessage += toupper(c);
        }
    }
    
    // Ensure message ends with a period
    if (!cleanMessage.empty() && cleanMessage.back() != '.') {
        cleanMessage += '.';
    }
    
    // Fill the grid with the message in diamond pattern
    grid.fillWithMessage(cleanMessage);
    
    // Fill empty cells with random uppercase letters
    grid.fillRandom();
    
    // Display the grid
    cout << "\nGrid after filling with message and random letters:\n";
    grid.print();
    
    // Read column-wise to create the encrypted message
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