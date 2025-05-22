#include "HandleException.hpp"
#include <string>
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

void HandleException::handleInvalidInput() {
    cin.clear(); // Clear the error flag
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
}


