#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <string>
#include <cmath>
#include "Encryptor.hpp"
#include "Decryptor.hpp"

class Grid {
private:
    int size;
    std::vector<std::vector<char>> matrix;

public:
    Grid(int gridSize);
    void setCell(int row, int col, char value);
    void fillWithMessage(const std::string& diamondMessage);
    void fillRandom();
    std::string readColumnWise() const;
    std::string extractMessage(bool stopAtPeriod) const;
    void print() const;
};

#endif
