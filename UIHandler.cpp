#include "UIHandler.hpp"
#include "Encryptor.hpp"
#include "Decryptor.hpp"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

void UIHandler::run() {
    while (true) {
        displayMenu();
    }
}

// Helper function to print a menu line with padding and borders
void printMenuLine(const string& text, int width) {
    int padLen = width - 3 - static_cast<int>(text.length()); // 3 = 2 asterisks + 1 space
    cout << "* " << text << string(padLen, ' ') << "*\n";
}

void UIHandler::displayMenu() {
    const int width = 24;
    cout << "\n" << string(width, '*') << "\n";
    printMenuLine("Menu - Level 1", width);
    printMenuLine("Select an option:", width);
    printMenuLine("1. Encrypt a message", width);
    printMenuLine("2. Decrypt a message", width);
    printMenuLine("3. Quit", width);
    cout << string(width, '*') << "\n";

    while (true) {
        int choice = getInt("Enter choice: ");
        if (choice < 1 || choice > 3) {
            cout << "Invalid option.\n";
            continue;
        } else if (choice == 1) {
            displayMenu2();
            break;
        } else if (choice == 2) {
            handleDecryption();
            break;
        } else if (choice == 3) {
            cout << "Exiting program...\n";
            exit(0);
        }
    }
}

void UIHandler::displayMenu2() {
    const int width = 40;
    cout << "\n" << string(width, '*') << "\n";
    printMenuLine("Menu Level 2 - Encryption", width);
    printMenuLine("Select an option:", width);
    printMenuLine("1. Enter a message", width);
    printMenuLine("2. One-round encryption", width);
    printMenuLine("3. Automatic multi-round encryption", width);
    printMenuLine("4. Back", width);
    cout << string(width, '*') << "\n";

    string message = "";

    while(true) {
        int choice = getInt("Enter choice: ");
        if (choice < 1 || choice > 4) {
            cout << "Invalid option.\n";
            continue;
        } 
        else if (choice == 1) {
            message = getLine("Enter a message to encrypt: ");
            cout << "Message set to: " << message << endl;
            continue;
        } else if (choice == 2 && message.empty()) {
            cout << "You must enter a message first. Select option 1.\n";
            continue;
        } else if (choice == 3 && message.empty()) {
            cout << "You must enter a message first. Select option 1.\n";
            continue;
        } else if (choice == 2 && !message.empty()) {
            displayMenu3a(message);
            break;
        } else if (choice == 3 && !message.empty()) {
            displayMenu3b(message);
            break;
        } else if (choice == 4) {
            cout << "Returning to main menu...\n";
            displayMenu();
            break;
        }
    }
}

void UIHandler::displayMenu3a(string& message) {
    const int width = 50;
    cout << "\n" << string(width, '*') << "\n";
    printMenuLine("Menu Level 3 - Encryption", width);
    printMenuLine("Select an option:", width);
    printMenuLine("1. Enter a grid size", width);
    printMenuLine("2. Automatic grid size", width);
    printMenuLine("3. Print the grid and the encoded message", width);
    printMenuLine("4. Back", width);
    cout << string(width, '*') << "\n";

    int gridSize = 0;
    int rounds = 1; // One-round encryption always uses 1 round

    while (true) {
        int choice = getInt("Enter choice: ");
        if (choice < 1 || choice > 4) {
            cout << "Invalid option.\n";
            continue;
        } else if (choice == 1) {
            gridSize = getInt("Enter grid size (must be odd): ");
            if (gridSize % 2 == 0) {
                cout << "Grid size must be odd. Try again.\n";
                continue;
            }
            cout << "Grid size set to: " << gridSize << endl;
            continue;
        } else if (choice == 2) {
            cout << "Using automatic grid size.\n";
            gridSize = 0; // 0 means auto
            continue;
        } else if (choice == 3) {
            cout << "Printing the grid and the encoded message...\n";
            handleEncryption(message, rounds, gridSize);
            break;
        } else if (choice == 4) {
            displayMenu2();
            break;
        }
    }
}

void UIHandler::displayMenu3b(string& message) {
    const int width = 75;
    cout << "\n" << string(width, '*') << "\n";
    printMenuLine("Menu Level 3 - Encryption", width);
    printMenuLine("Select an option:", width);
    printMenuLine("1. Enter the round number", width);
    printMenuLine("2. For each round, print the grid and the corresponding encoded message", width);
    printMenuLine("3. Back", width);
    cout << string(width, '*') << "\n";

    int rounds = 3; // Default to 3 rounds
    int gridSize = 0; // Default to automatic grid size

    while (true) {
        int choice = getInt("Enter choice: ");
        if (choice < 1 || choice > 3) {
            cout << "Invalid option.\n";
            continue;
        } else if (choice == 1) {
            rounds = getInt("Enter the number of rounds: ");
            if (rounds <= 0) {
                cout << "Number of rounds must be positive. Setting to default (3).\n";
                rounds = 3;
            } else {
                cout << "Number of rounds set to: " << rounds << endl;
            }
            continue;
        } else if (choice == 2) {
            cout << "Printing the grid and the encoded message for " << rounds << " rounds...\n";
            handleEncryption(message, rounds, gridSize);
            break;
        } else if (choice == 3) {
            displayMenu2();
            break;
        }
    }
}

void UIHandler::handleEncryption(string& message, int& rounds, int& gridSize) {
    Encryptor encryptor;
    
    // For multi-round encryption, we need to show each round's results
    if (rounds > 1) {
        string intermediateMsg = message;
        
        for (int r = 1; r <= rounds; r++) {
            cout << "\n--- Round " << r << " of " << rounds << " ---\n";
            int currentGridSize = (gridSize == 0) ? encryptor.computeGrid(intermediateMsg) : gridSize;
            cout << "Using grid size: " << currentGridSize << endl;
            
            // Process just one round at a time
            intermediateMsg = encryptor.processEncryption(intermediateMsg, currentGridSize);
            
            cout << "After round " << r << ", message is: " << intermediateMsg << endl;
        }
        
        cout << "\nFinal encrypted message: " << intermediateMsg << endl;
    } else {
        // One-round encryption
        string encryptedMessage = encryptor.encrypt(message, rounds, gridSize);
        cout << "Encrypted message: " << encryptedMessage << endl;
    }
}

void UIHandler::handleDecryption() {
    string encryptedMessage = getLine("Enter the encrypted message: ");
    int rounds = getInt("Enter the number of rounds used in encryption: ");
    
    if (rounds <= 0) {
        cout << "Number of rounds must be positive. Using 1 round.\n";
        rounds = 1;
    }

    Decryptor decryptor;
    
    // For multi-round decryption, show each intermediate step
    if (rounds > 1) {
        string intermediateMsg = encryptedMessage;
        
        for (int r = 1; r <= rounds; r++) {
            cout << "\n--- Decryption Round " << r << " of " << rounds << " ---\n";
            
            // Process just one round of decryption
            intermediateMsg = decryptor.processDecryption(intermediateMsg);
            
            cout << "After decryption round " << r << ", message is: " << intermediateMsg << endl;
        }
        
        cout << "\nFinal decrypted message: " << intermediateMsg << endl;
    } else {
        // One-round decryption
        string decryptedMessage = decryptor.decrypt(encryptedMessage, rounds);
        cout << "Decrypted message: " << decryptedMessage << endl;
    }
}

string UIHandler::getLine(const string& prompt) {
    cout << prompt;
    string input;
    getline(cin >> ws, input);
    return input;
}

int UIHandler::getInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter an integer.\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the rest of the line
            return value;
        }
    }
}