#include <fstream>
#include <iostream>
#include <cassert>
#include <algorithm>


void parse_grid(char grid[10][10]) {
    std::ifstream input("p11.txt");

    char digit;
    int idx = 0;
    while (input >> digit) {
        digit -= '0';
        if (digit >= 0 && digit <= 9) {
            grid[idx / 10][idx % 10] = digit;
            idx++;
        }
    }
    assert(idx == 100);
}

int step(char grid[10][10]) {
    int iters = 0;
    while (true) {
        bool flashed = false;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                char &digit = grid[i][j];
                if (iters == 0) {
                    digit++;
                }
                if (digit > 9 && digit < 100) {
                    flashed = true;
                    digit += 100;
                    for (int ii = std::max(i - 1, 0); ii < std::min(i + 2, 10); ii++) {
                        for (int jj = std::max(j - 1, 0); jj < std::min(j + 2, 10); jj++) {
                            char &adjacent = grid[ii][jj];
                            adjacent++;
                        }
                    }
                }
            }
        }

        if (!flashed) {
            break;
        }
        iters++;
    }
    int flashes = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            char &digit = grid[i][j];
            if (digit > 9) {
                digit = 0;
                flashes++;
            }
        }
    }
    return flashes;
}


void print(char grid[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j] == 0) {
                std::cout << "\033[1;31m" << int(grid[i][j]) << "\033[0m";
            } else {
                std::cout << int(grid[i][j]);
            }
        }
        std::cout << std::endl;

    }
    std::cout << std::endl;

}


int main (int argc, char** argv) {
    char grid[10][10];
    parse_grid(grid);
    print(grid);

    long total_flashes = 0;
    for (int i = 0; i < 100; i++) {
        total_flashes += step(grid);
        if (argc > 1) {
            print(grid);
        }
    }
    std::cout << "Number of flashes: " << total_flashes << std::endl;

    parse_grid(grid);
    int i = 0;
    int count = 0;
    while (count != 100) {
        count = step(grid);
        i++;
    }
    std::cout << "Number of iters: " << i << std::endl;

    return 0;
}
