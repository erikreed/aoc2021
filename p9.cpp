#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <numeric>
#include <algorithm>
#include <memory>
#include <map>
#include <queue>

long prod_three_largest_components(std::vector<char*> &grid, int cols) {
    bool* traversed = new bool[grid.size() * cols]();
    std::map<int, int> component_sizes;
    std::queue<std::pair<int, int>> frontier;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < cols; j++) {
            int component_id = component_sizes.size();
            frontier.emplace(i, j);
            while (!frontier.empty()) {
                auto next = frontier.front();
                frontier.pop();

                int ii = next.first;
                int jj = next.second;
                int idx = ii * cols + jj;
                assert(ii >= 0 && ii < grid.size());
                assert(jj >= 0 && jj < cols);
                char digit = grid[ii][jj];

                if (traversed[idx]) {
                    continue;
                }
                traversed[idx] = true;
                if (digit != 9) {
                    component_sizes[component_id]++;
                    frontier.emplace(std::max(ii - 1, 0), jj);
                    frontier.emplace(std::min(ii + 1, int(grid.size() - 1)), jj);
                    frontier.emplace(ii, std::max(jj - 1, 0));
                    frontier.emplace(ii, std::min(jj + 1, cols - 1));
                }
            }
        }
    }

    delete[] traversed;

    assert(component_sizes.size() >= 3);
    std::cout << "Basin sizes:" << std::endl;
    std::vector<int> sizes;
    for (auto& item : component_sizes) {
        sizes.push_back(item.second);
    }
    std::sort(sizes.begin(), sizes.end());
    return long(sizes[sizes.size() - 1]) * sizes[sizes.size() - 2] * sizes[sizes.size() - 3];
}

int main(int argc, char** argv) {
    std::ifstream input("p9.txt");
    std::string line;
    std::vector<char*> grid;
    while (std::getline(input, line)) {
        char* digits = new char[line.size()];
        int i = 0;
        for (char c : line) {
            char digit = char(c - '0');
            assert(digit >= 0 && digit <= 9);
            digits[i++] = digit;
        }
        grid.push_back(digits);
    }
    const int cols = line.size();
    std::cout << "Parsed " << grid.size() << " lines" << std::endl;

    long risk_level = 0;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < cols; j++) {
            char digit = grid[i][j];
            
            if (i > 0 && digit >= grid[i-1][j]) {
                continue;
            } else if (i < grid.size() - 1 && digit >= grid[i+1][j]) {
                continue;
            } else if (j > 0 && digit >= grid[i][j - 1]) {
                continue;
            } else if (j < cols - 1 && digit >= grid[i][j+1]) {
                continue;
            }
            risk_level += digit + 1;
        }
    }

    std::cout << "Total risk_level: " << risk_level << std::endl;
    std::cout << "Product 3 largest basins: " << prod_three_largest_components(grid, cols) << std::endl;
    // 61564752 too high
    for (auto& row : grid) delete[] row;
    return 0;
}
