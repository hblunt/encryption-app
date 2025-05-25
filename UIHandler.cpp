#include "UIHandler.hpp"
#include "Encryptor.hpp"
#include "Decryptor.hpp"
#include "HandleException.hpp"
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
    // 3 = 2 asterisks + 1 space
    int padLen = width - 3 - static_cast<int>(text.length()); 
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
        try {
            if (choice < 1 || choice > 3) {
                throw HandleException("Out of range. Please try again.\nPress Enter to continue.");
                continue;
            } else if (choice == 1) {
                displayMenu2a();
                break;
            } else if (choice == 2) {
                displayMenu2b();
                break;
            } else if (choice == 3) {
                cout << "Exiting program...\n";
                exit(0);
            }
            else {
                throw HandleException("Invalid choice. Please try again.\nPress Enter to continue.");
                continue;
            }
        } catch (const HandleException& e) {
            cout << e.what() << endl;
            HandleException::handleInvalidInput();
            continue;
        }
    }
}

void UIHandler::displayMenu2a() {
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
        try {
            int choice = getInt("Enter choice: ");
            if (choice < 1 || choice > 4) {
                throw HandleException("Out of range. Please try again.\nPress Enter to continue.");
                continue;
            } 
            else if (choice == 1) {
                message = getLine("Enter a message to encrypt: ");
                cout << "Message set to: " << message << endl;
                continue;
            } else if (choice == 2 && message.empty()) {
                throw HandleException("You must enter a message before selecting this option. Select option 1.\nPress Enter to continue.");
                continue;
            } else if (choice == 3 && message.empty()) {
                throw HandleException("You must enter a message before selecting this option. Select option 1.\nPress Enter to continue.");
                continue;
            } else if (choice == 2 && !message.empty()) {
                displayMenu3a(message);
                break;
            } else if (choice == 3 && !message.empty()) {
                displayMenu3b(message);
                break;
            } else if (choice == 4) {
                displayMenu();
                break;
            } else {
                throw HandleException("Invalid choice. Please try again.\nPress Enter to continue.");
                continue;
            }
        } catch(const HandleException& e) {
            cout << e.what() << endl;
            HandleException::handleInvalidInput();
            continue;
        }
    }
}

void UIHandler::displayMenu2b(){
    const int width = 80;
    cout << "\n" << string(width, '*') << "\n";
    printMenuLine("Menu Level 2 - Decryption", width);
    printMenuLine("Select an option:", width);
    printMenuLine("1. Enter a message", width);
    printMenuLine("2. Enter the round number", width);
    printMenuLine("3. For each round, print the grid and the corresponding decoded message", width);
    printMenuLine("4. Back", width);
    cout << string(width, '*') << "\n";

    string message = "";
    int rounds = 1;

    while(true) {
        try {
            int choice = getInt("Enter choice: ");
            if (choice < 1 || choice > 4) {
                throw HandleException("Out of range. Please try again.\nPress Enter to continue.");
                continue;
            } 
            else if (choice == 1) {
                message = getLine("Enter a message to decrypt: ");
                cout << "Message set to: " << message << endl;
                continue;
            } else if (choice == 2 && !message.empty()) {
                rounds = getInt("Enter the number of rounds used in encryption: ");
                continue;
            } else if (choice == 2 && message.empty()) {
                throw HandleException("You must enter a message before selecting this option. Select option 1.\nPress Enter to continue.");
                continue;
            } else if (choice == 3 && rounds <= 0) {
                throw HandleException("Rounds must be positive. Please enter a valid number.\nPress Enter to continue.");
                continue;
            } else if (choice == 3 && message.empty()) {
                throw HandleException("You must enter a message before selecting this option. Select option 1.\nPress Enter to continue.");
                continue;
            } else if (choice == 2 && !message.empty()) {
                handleDecryption(message, rounds);
                break;
            } else if (choice == 3 && !message.empty()) {
                handleDecryption(message, rounds);
                break;
            } else if (choice == 4) {
                displayMenu();
                break;
            } else {
                throw HandleException("Invalid choice. Please try again.\nPress Enter to continue.");
                continue;
            }
        } catch (const HandleException& e) {
            cout << e.what() << endl;
            HandleException::handleInvalidInput();
            continue;
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
    int rounds = 1;

    while (true) {
        int choice = getInt("Enter choice: ");
        try{
            if (choice < 1 || choice > 4) {
                throw HandleException("Out of range. Please try again.\nPress Enter to continue.");
                continue;
            } else if (choice == 1) {
                gridSize = getInt("Enter grid size (must be odd): ");
                if (gridSize % 2 == 0) {
                    throw HandleException("Grid size must be odd. Please enter a valid number.\nPress Enter to continue.");
                    continue;
                }
                cout << "Grid size set to: " << gridSize << endl;
                continue;
            } else if (choice == 2) {
                cout << "Using automatic grid size.\n";
                gridSize = 0; // 0 means auto
                continue;
            } else if (choice == 3 && gridSize <= 0) {
                throw HandleException("Grid size must be positive. Please enter a valid number.\nPress Enter to continue.");
                continue;
            } else if (choice == 3) {
                cout << "Printing the grid and the encoded message...\n";
                handleEncryption(message, rounds, gridSize);
                break;
            } else if (choice == 4) {
                displayMenu2a();
                break;
            } else {
                throw HandleException("Invalid choice. Please try again.\nPress Enter to continue.");
                continue;
            }
        } catch (const HandleException& e) {
            cout << e.what() << endl;
            HandleException::handleInvalidInput();
            continue;
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

    int rounds = 3;
    int gridSize = 0;

    while (true) {
        try{
            int choice = getInt("Enter choice: ");
            if (choice < 1 || choice > 3) {
                throw HandleException("Out of range. Please try again.\nPress Enter to continue.");
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
                displayMenu2a();
                break;
            } else {
                throw HandleException("Invalid choice. Please try again.\nPress Enter to continue.");
                continue;
            }
        } catch (const HandleException& e) {
            cout << e.what() << endl;
            HandleException::handleInvalidInput();
            continue;
        }
    }
}

void UIHandler::handleEncryption(string& message, int& rounds, int& gridSize) {
    Encryptor encryptor;
    string current_message_state = message;

    // Remove non-alphabetic characters and convert to uppercase
    string prepared_message;
    for (char c : current_message_state) {
        if (isalpha(c)) {
            prepared_message += toupper(c);
        }
    }

    // Append a period if it's not already the last character or if empty
    if (prepared_message.empty() || prepared_message.back() != '.') {
        prepared_message += '.';
    }
    current_message_state = prepared_message;

    if (rounds > 1) {
        string intermediateMsg = current_message_state; // Start with the prepared message

        for (int r = 1; r <= rounds; r++) {
            cout << "\n--- Round " << r << " of " << rounds << " ---\n";
            // computeGrid should use the current state of the message for this round
            int currentRoundGridSize = (gridSize == 0) ? encryptor.computeGrid(intermediateMsg) : gridSize;
            cout << "Using grid size: " << currentRoundGridSize << endl;

            intermediateMsg = encryptor.processEncryption(intermediateMsg, currentRoundGridSize); 

            cout << "After round " << r << ", message is: " << intermediateMsg << endl;
        }
        cout << "\nFinal encrypted message: " << intermediateMsg << endl;
    } else { 
        // Single round encryption
        int currentRoundGridSize = (gridSize == 0) ? encryptor.computeGrid(current_message_state) : gridSize;
        string encryptedMessage = encryptor.processEncryption(current_message_state, currentRoundGridSize);
        cout << "Encrypted message: " << encryptedMessage << endl;
    }
}

void UIHandler::handleDecryption(string& message, int& rounds) {

    Decryptor decryptor;
    
    if (rounds > 1) {
        string intermediateMsg = message;
        for (int r = 1; r <= rounds; r++) {
            cout << "\n--- Decryption Round " << r << " of " << rounds << " ---\n";
            
            // Calculate grid size for this round
            int gridSize = 1;
            while (gridSize * gridSize < intermediateMsg.length()) {
                gridSize += 2;
            }
            cout << "Grid size for this round: " << gridSize << endl;
            
            // Process decryption for this round
            bool isFinalExtraction = (r == rounds);
            intermediateMsg = decryptor.processDecryption(intermediateMsg, isFinalExtraction);
            
            if (intermediateMsg.rfind("Error:", 0) == 0) {
                cout << intermediateMsg << endl;
                break;
            }
            
            cout << "After decryption round " << r << ", message is: " << intermediateMsg << endl;
            
            // If not the final round, prepare for the next round
            if (r < rounds) {

                // Find the largest odd number whose square is less than or equal to the current message to this length
                int nextGridSize = 1;
                while ((nextGridSize + 2) * (nextGridSize + 2) <= intermediateMsg.length()) {
                    nextGridSize += 2;
                }
                
                int targetLength = nextGridSize * nextGridSize;
                
                int charsToRemove = intermediateMsg.length() - targetLength;
                
                if (charsToRemove > 0) {
                    cout << "Trimming " << charsToRemove << " characters to get a perfect square length of " 
                         << targetLength << " (grid size " << nextGridSize << ")" << endl;
                    
                    intermediateMsg = intermediateMsg.substr(0, targetLength);
                    cout << "Trimmed message: " << intermediateMsg << endl;
                }
            }
        }
        
        if (intermediateMsg.rfind("Error:", 0) != 0) {
            cout << "\nFinal decrypted message: " << intermediateMsg << endl;
        }
    } else {
        // Single-round decryption
        string decryptedMessage = decryptor.processDecryption(message, true);
        cout << "Decrypted message: " << decryptedMessage << endl;
    }
}

// Additional helper functions for input handling

string UIHandler::getLine(const string& prompt) {
    string input;
    while(true) {
        try {
            cout << prompt;
            getline(cin, input);
            if (input.empty()) {
                throw HandleException("Input cannot be empty. Please try again.");
            }
            return input;
        }
        catch (const HandleException& e) {
            cout << e.what() << endl;
        }
    }
}

int UIHandler::getInt(const string& prompt) {
    int value;
    while (true) {
        try {
            cout << prompt;
            cin >> value;
            // Clear the input buffer to handle any leftover characters
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (cin.fail()) {
                throw HandleException("Invalid input. Please enter an integer.");
            }
            if (value < 0) {
                throw HandleException("Negative numbers are not allowed. Please enter a positive integer.\nPress Enter to continue.");
            }
            return value;
        } catch (const HandleException& e) {
            cout << e.what() << endl;
            HandleException::handleInvalidInput();
        }
    }
}