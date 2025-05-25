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
    explicit HandleException(const std::string& msg) : message(msg) {}
    
    const char* what() const noexcept override {
        return message.c_str();
    }
    static void handleInvalidInput();
};

#endif