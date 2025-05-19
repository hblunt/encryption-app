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
// In Grid.cpp
// void Grid::fillWithMessage(const string& original) { // Original parameter name
void Grid::fillWithMessage(const string& text_to_place_in_diamond) { // Suggested new parameter name

    // REMOVE the block that did:
    // string message;
    // for (char c : original) {
    //     if (isalpha(c)) { message += toupper(c); }
    // }
    // if (message.empty() || message.back() != '.') { message += '.'; }

    // The rest of your diamond filling logic should remain,
    // but it must use 'text_to_place_in_diamond' and 'text_to_place_in_diamond.length()'
    // instead of the internal 'message' variable you were creating.
    // For example:
    int mid = size / 2;
    int msgIndex = 0;

    for (int layer = mid; layer >= 0 && msgIndex < text_to_place_in_diamond.length(); --layer) {
        int i = mid;
        int j = mid - layer;
        // ... (Your existing diamond traversal logic using text_to_place_in_diamond[msgIndex++])
        // For example, a line like:
        // if (msgIndex < message.length()) matrix[i][j] = message[msgIndex++];
        // becomes:
        // if (msgIndex < text_to_place_in_diamond.length()) matrix[i][j] = text_to_place_in_diamond[msgIndex++];
        // Ensure all such occurrences are updated.
        // (The loops from your provided Grid.cpp are quite specific, ensure they correctly use text_to_place_in_diamond)
         // Path 1 from your code
        while (i > mid - layer && j < mid) {
            if (msgIndex < text_to_place_in_diamond.length()) matrix[i][j] = text_to_place_in_diamond[msgIndex++]; else break;
            i--; j++;
            if (msgIndex >= text_to_place_in_diamond.length() && layer > 0 && i <= mid - layer && j >= mid) break; 
        }
        if (msgIndex >= text_to_place_in_diamond.length() && layer > 0 && !(layer == 0 && i == mid && j == mid)) break;

        // Path 2 from your code
        while (i < mid && j < mid + layer) {
            if (msgIndex < text_to_place_in_diamond.length()) matrix[i][j] = text_to_place_in_diamond[msgIndex++]; else break;
            i++; j++;
            if (msgIndex >= text_to_place_in_diamond.length() && layer > 0 && i >= mid && j >= mid + layer) break;
        }
        if (msgIndex >= text_to_place_in_diamond.length() && layer > 0 && !(layer == 0 && i == mid && j == mid)) break;

        // Path 3 from your code
        while (i < mid + layer && j > mid) {
            if (msgIndex < text_to_place_in_diamond.length()) matrix[i][j] = text_to_place_in_diamond[msgIndex++]; else break;
            i++; j--;
            if (msgIndex >= text_to_place_in_diamond.length() && layer > 0 && i >= mid + layer && j <= mid) break;
        }
        if (msgIndex >= text_to_place_in_diamond.length() && layer > 0 && !(layer == 0 && i == mid && j == mid)) break;

        // Path 4 from your code
        while (i > mid && j > mid - layer) {
            if (msgIndex < text_to_place_in_diamond.length()) matrix[i][j] = text_to_place_in_diamond[msgIndex++]; else break;
            i--; j--;
            if (msgIndex >= text_to_place_in_diamond.length() && layer > 0 && i <= mid && j <= mid - layer) break;
        }
        if (msgIndex >= text_to_place_in_diamond.length() && layer > 0 && !(layer == 0 && i == mid && j == mid)) break;

        // Center cell
        if (layer == 0 && msgIndex < text_to_place_in_diamond.length()) {
            matrix[mid][mid] = text_to_place_in_diamond[msgIndex++];
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

std::string Grid::extractMessage(bool stopAtPeriod) const {
    std::string result;
    int mid = size / 2;

    // Your existing diamond traversal logic
    for (int layer = mid; layer >= 0; --layer) {
        int i = mid;
        int j = mid - layer;
        
        // This is a simplified representation of your 4 paths and center point.
        // You'll need to integrate the 'stopAtPeriod' check into each character read operation
        // within your existing diamond traversal loops.

        // Example for one path (you have 4 such loops + center cell logic)
        // Path 1: Up and right to top (from your original extractMessage)
        while (i > mid - layer && j < mid) {
            // It's good practice to ensure i and j are within bounds [0, size-1]
            // before accessing matrix[i][j], though your loop conditions might already ensure this.
            if (i >= 0 && i < size && j >= 0 && j < size) { // Basic bounds check
                char ch = matrix[i][j];
                if (stopAtPeriod && ch == '.') {
                    return result; // Stop and return if flag is true and char is '.'
                }
                result += ch;
            }
            i--;
            j++;
        }
        // Path 2: Top to rightmost
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
        // Path 3: Rightmost to bottom
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
        // Path 4: Bottom to leftmost
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

        // Center cell for innermost layer
        if (layer == 0) {
            if (mid >= 0 && mid < size) { // Check bounds for mid
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

void Grid::print() const {
    for (const auto& row : matrix) {
        for (char ch : row) cout << ch << ' ';
        cout << '\n';
    }
}
