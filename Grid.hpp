#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <string>

class Grid {
private:
    int size;
    

public:
    std::vector<std::vector<char>> matrix;
    Grid(int gridSize);
    void fillWithMessage(const std::string& message);
    void fillRandom();
    std::string readColumnWise() const;
    std::string extractMessage() const;
    void print() const;
};

#endif
