#include "Grid.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <string>
#include <vector>
#include "HandleException.hpp"

using namespace std;

Grid::Grid(int gridSize) : size(gridSize), matrix(gridSize, vector<char>(gridSize, ' ')) {
    srand(static_cast<unsigned>(time(nullptr)));
}

void Grid::setCell(int row, int col, char value) {
    if (row >= 0 && row < size && col >= 0 && col < size) {
        matrix[row][col] = value;
    } else {
        throw HandleException("Invalid cell indices for setting value in grid.");
    }
}

void Grid::fillWithMessage(const string& diamondMessage) {

    int mid = size / 2;
    size_t msgIndex = 0;
    size_t diamondLength = diamondMessage.length();

    for (int layer = mid; layer >= 0 && msgIndex < diamondLength; --layer) {
        int i = mid;
        int j = mid - layer;

         // Move diagonally right and up
        while (i > mid - layer && j < mid) {
            if (msgIndex < diamondLength) matrix[i][j] = diamondMessage[msgIndex++]; else break;
            i--; j++;
            if (msgIndex >= diamondLength && layer > 0 && i <= mid - layer && j >= mid) break; 
        }
        if (msgIndex >= diamondLength && layer > 0 && !(layer == 0 && i == mid && j == mid)) break;

        // Move diagonally right and down
        while (i < mid && j < mid + layer) {
            if (msgIndex < diamondLength) matrix[i][j] = diamondMessage[msgIndex++]; else break;
            i++; j++;
            if (msgIndex >= diamondLength && layer > 0 && i >= mid && j >= mid + layer) break;
        }
        if (msgIndex >= diamondLength && layer > 0 && !(layer == 0 && i == mid && j == mid)) break;

        // Move diagonally left and down
        while (i < mid + layer && j > mid) {
            if (msgIndex < diamondLength) matrix[i][j] = diamondMessage[msgIndex++]; else break;
            i++; j--;
            if (msgIndex >= diamondLength && layer > 0 && i >= mid + layer && j <= mid) break;
        }
        if (msgIndex >= diamondLength && layer > 0 && !(layer == 0 && i == mid && j == mid)) break;

        // Move diagonally left and up
        while (i > mid && j > mid - layer) {
            if (msgIndex < diamondLength) matrix[i][j] = diamondMessage[msgIndex++]; else break;
            i--; j--;
            if (msgIndex >= diamondLength && layer > 0 && i <= mid && j <= mid - layer) break;
        }
        if (msgIndex >= diamondLength && layer > 0 && !(layer == 0 && i == mid && j == mid)) break;

        // Center cell
        if (layer == 0 && msgIndex < diamondLength) {
            matrix[mid][mid] = diamondMessage[msgIndex++];
        }
    }
}

// Fill the remaining empty spaces with random letters
void Grid::fillRandom() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == ' ') {
                matrix[i][j] = 'A' + (rand() % 26);
            }
        }
    }
}

// Read grid column by column and return the result as a string
string Grid::readColumnWise() const {
    string result;
    for (int col = 0; col < size; ++col) {
        for (int row = 0; row < size; ++row) {
            result += matrix[row][col];
        }
    }
    return result;
}

string Grid::extractMessage(bool stopAtPeriod) const {
    string result;
    int mid = size / 2;

    // Traverse the same diamond pattern as fillWithMessage
    for (int layer = mid; layer >= 0; --layer) {
        int i = mid;
        int j = mid - layer;
        
        while (i > mid - layer && j < mid) {
            if (i >= 0 && i < size && j >= 0 && j < size) { 
                char ch = matrix[i][j];
                if (stopAtPeriod && ch == '.') {
                    return result;
                }
                result += ch;
            }
            i--;
            j++;
        }
        
        while (i < mid && j < mid + layer) {
             if (i >= 0 && i < size && j >= 0 && j < size) {
                char ch = matrix[i][j];
                if (stopAtPeriod && ch == '.') {
                    return result;
                }
                result += ch;
            }
            i++;
            j++;
        }
        
        while (i < mid + layer && j > mid) {
            if (i >= 0 && i < size && j >= 0 && j < size) {
                char ch = matrix[i][j];
                if (stopAtPeriod && ch == '.') {
                    return result;
                }
                result += ch;
            }
            i++;
            j--;
        }
        
        while (i > mid && j > mid - layer) {
            if (i >= 0 && i < size && j >= 0 && j < size) {
                char ch = matrix[i][j];
                if (stopAtPeriod && ch == '.') {
                    return result;
                }
                result += ch;
            }
            i--;
            j--;
        }

        if (layer == 0) {
            if (mid >= 0 && mid < size) { 
                 char ch = matrix[mid][mid];
                 if (stopAtPeriod && ch == '.') {
                     return result;
                 }
                 result += ch;
            }
        }
    }
    return result;
}

// Print the grid to the console
void Grid::print() const {
    for (const auto& row : matrix) {
        for (char ch : row) cout << ch << ' ';
        cout << '\n';
    }
}
