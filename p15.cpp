#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <cassert>

#define MULTIPLIER 5
#define ROWS (100 * MULTIPLIER)
#define COLS (100 * MULTIPLIER)

struct Node {
    char cost = -1;
    long best = 999999999L;
    std::pair<int, int> coord;
    Node* previous = nullptr;

    std::vector<Node*> neighbors(Node grid[ROWS][COLS]) {
        std::vector<Node*> neighbors;        
        auto first = coord.first;
        auto second = coord.second;
        if (first > 0) {
            neighbors.push_back(&grid[first - 1][second]);
        }
        if (first < ROWS - 1) {
            neighbors.push_back(&grid[first + 1][second]);
        }
        if (second > 0) {
            neighbors.push_back(&grid[first][second - 1]);
        }
        if (second < COLS - 1) {
            neighbors.push_back(&grid[first][second + 1]);
        }
        return neighbors;
    }
};

void print(Node grid[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            const auto &node = grid[i][j];
            std::cout << std::to_string(node.cost);
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


int main(int argc, char** argv) {
    Node grid[ROWS][COLS];
    std::ifstream input("p15.txt");
    std::string line;

    int i = 0;
    while (input >> line) {
        int j = 0;
        for (char c : line) {
            grid[i][j].cost = c - '0';
            grid[i][j].coord = std::make_pair(i, j);
            j++;
        }
        assert(j == COLS / MULTIPLIER);
        i++;
    }
    assert(i == ROWS / MULTIPLIER);
    std::cout << "Parsed " << i << " lines" << std::endl;

    for (i = 0; i < ROWS / MULTIPLIER; i++) {
        for (int j = 0; j < COLS / MULTIPLIER; j++) {
            const auto &node = grid[i][j];

            for (int quadrantX = 0; quadrantX < MULTIPLIER; quadrantX++ ) { 
                for (int quadrantY = 0; quadrantY < MULTIPLIER; quadrantY++ ) {
                    int x = (ROWS / MULTIPLIER) * quadrantX + i;
                    int y = (COLS / MULTIPLIER) * quadrantY + j;
                    auto &mirrored = grid[x][y];
                    mirrored.coord = std::make_pair(x, y);
                    int cost = node.cost + quadrantX + quadrantY;
                    while (cost > 9) {
                        cost -= 9;
                    }
                    mirrored.cost = cost;
                }        
            }
        }
    }

    grid[0][0].best = 0;
    auto cmp = [](Node* left, Node* right) { return left->best > right->best; };
    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> frontier(cmp);
    frontier.push(&grid[0][0]);
    while (!frontier.empty()) {
        auto &next = *frontier.top();
        frontier.pop();
        
        std::pair<int, int> &coord = next.coord;
        for (auto neighbor : grid[coord.first][coord.second].neighbors(grid)) {
            auto cost = neighbor->cost + next.best;
            if (cost < neighbor->best) {
                neighbor->best = cost;
                neighbor->previous = &next;
                frontier.push(neighbor);
            }
        }
    }
    std::cout << "Traversal complete" << std::endl;
    std::cout << "Path: ";
    const auto* next = &grid[ROWS - 1][COLS - 1];
    const auto* end = next;
    while (next) {
        std::cout << next->coord.first << "," << next->coord.second << " ";
        assert(next->cost > 0);
        next = next->previous;
    }
    
    std::cout << std::endl;
    std::cout << "Cost to reach grid end: " << grid[ROWS - 1][COLS - 1].best << std::endl;
    return 0;
}