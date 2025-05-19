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

// In Encryptor.cpp
string Encryptor::processEncryption(const string& message_for_this_round, int gridSize_for_this_round) {
    Grid grid(gridSize_for_this_round);

    // REMOVE the block that did:
    // string cleanMessage;
    // for (char c : message) { ... }
    // if (!cleanMessage.empty() && cleanMessage.back() != '.') { ... }
    // grid.fillWithMessage(cleanMessage);

    // USE message_for_this_round DIRECTLY:
    grid.fillWithMessage(message_for_this_round); 

    grid.fillRandom();

    cout << "\nGrid after filling with message and random letters:\n"; // As per spec [cite: 13]
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