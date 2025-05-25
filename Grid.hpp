#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <string>
#include <cmath>

class Grid {
private:
    int size;

public:
    std::vector<std::vector<char>> matrix;
    Grid(int gridSize);
    void fillWithMessage(const std::string& diamondMessage);
    void fillRandom();
    std::string readColumnWise() const;
    std::string extractMessage(bool stopAtPeriod) const;
    void print() const;
};

#endif
