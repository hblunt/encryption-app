#ifndef HANDLEEXCEPTION_HPP
#define HANDLEEXCEPTION_HPP

#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>

class HandleException : public std::exception {
private:
    std::string message;

public:
    // Constructor that takes an error message
    explicit HandleException(const std::string& msg) : message(msg) {}
    
    // Override the what() method from std::exception
    const char* what() const noexcept override {
        return message.c_str();
    }
\
    static void handleInvalidInput();
    static void handleOutOfRange();
};

#endif