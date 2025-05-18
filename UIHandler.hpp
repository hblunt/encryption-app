#ifndef UIHANDLER_HPP
#define UIHANDLER_HPP

#include <string>

class UIHandler {
public:
    void run();

private:
    void displayMenu();
    void displayMenu2();
    void displayMenu3a(std::string& message);
    void displayMenu3b(std::string& message);
    void handleEncryption(std::string& message, int& rounds, int& gridSize);
    void handleDecryption();

    std::string getLine(const std::string& prompt);
    int getInt(const std::string& prompt);
};

#endif
