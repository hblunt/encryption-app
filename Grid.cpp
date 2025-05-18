#include "Grid.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

Grid::Grid(int gridSize) : size(gridSize), matrix(gridSize, vector<char>(gridSize, ' ')) {
    srand(static_cast<unsigned>(std::time(nullptr)));
}

void Grid::fillWithMessage(const string& original) {
    // TODO: Implement diamond pattern placement
    string message;
    for (char c : original) {
        if (isalpha(c)) {
            message += toupper(c);
        }
    }

    if (message.empty() || message.back() != '.') {
        message += '.';
    }

    int mid = size / 2;
    int msgIndex = 0;

    // Fill the diamond from the outermost layer inwards
    for (int layer = mid; layer >= 0 && msgIndex < message.length(); --layer) {
        // 1. Start at leftmost cell of this layer
        int i = mid;
        int j = mid - layer;
        if (j < 0 || j >= size) continue;

        // Up and right to top
        while (i > mid - layer && j < mid) {
            if (msgIndex < message.length())
                matrix[i][j] = message[msgIndex++];
            i--;
            j++;
        }
        // Top to rightmost (right and down)
        while (i < mid && j < mid + layer) {
            if (msgIndex < message.length())
                matrix[i][j] = message[msgIndex++];
            i++;
            j++;
        }
        // Rightmost to bottom (down and left)
        while (i < mid + layer && j > mid) {
            if (msgIndex < message.length())
                matrix[i][j] = message[msgIndex++];
            i++;
            j--;
        }
        // Bottom to leftmost (left and up)
        while (i > mid && j > mid - layer) {
            if (msgIndex < message.length())
                matrix[i][j] = message[msgIndex++];
            i--;
            j--;
        }
        // Fill the center if we're at the innermost layer
        if (layer == 0 && msgIndex < message.length()) {
            matrix[mid][mid] = message[msgIndex++];
        }
    }
}

void Grid::fillRandom() {
    // TODO: Fill empty grid spots with random uppercase letters
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == ' ') {
                matrix[i][j] = 'A' + (rand() % 26);
            }
        }
    }
}

string Grid::readColumnWise() const {
    // TODO: Read grid column by column and return as string
    string result;
    for (int col = 0; col < size; ++col) {
        for (int row = 0; row < size; ++row) {
            result += matrix[row][col];
        }
    }
    cout << "Column-wise read: " << result << endl;
    return result;
}

string Grid::extractMessage() const {
    int mid = size / 2;
    string result;

    for (int layer = mid; layer >= 0; --layer) {
        // 1. Start at leftmost cell of this layer
        int i = mid;
        int j = mid - layer;
        if (j < 0 || j >= size) continue;

        // Up and right to top
        while (i > mid - layer && j < mid) {
            char ch = matrix[i][j];
            if (ch == '.') return result;
            result += ch;
            i--;
            j++;
        }
        // Top to rightmost (right and down)
        while (i < mid && j < mid + layer) {
            char ch = matrix[i][j];
            if (ch == '.') return result;
            result += ch;
            i++;
            j++;
        }
        // Rightmost to bottom (down and left)
        while (i < mid + layer && j > mid) {
            char ch = matrix[i][j];
            if (ch == '.') return result;
            result += ch;
            i++;
            j--;
        }
        // Bottom to leftmost (left and up)
        while (i > mid && j > mid - layer) {
            char ch = matrix[i][j];
            if (ch == '.') return result;
            result += ch;
            i--;
            j--;
        }
        // Center cell for innermost layer
        if (layer == 0) {
            char ch = matrix[mid][mid];
            if (ch == '.') return result;
            result += ch;
        }
    }
    return result;
}

void Grid::print() const {
    for (const auto& row : matrix) {
        for (char ch : row) cout << ch << ' ';
        cout << '\n';
    }
}
