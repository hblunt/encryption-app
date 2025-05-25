#include "HandleException.hpp"
#include <string>
#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

void HandleException::handleInvalidInput() {
    // Clear input buffer and discard invalid input
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}


