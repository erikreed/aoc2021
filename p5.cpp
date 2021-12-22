#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <numeric>
#include <algorithm>


struct Line {
    int x1, x2, y1, y2;

    bool diagonal() const {
        return !(x1 == x2 || y1 == y2);
    }
    int ymin() const {
        return std::min(y1, y2);
    }
    int ymax() const {
        return std::max(y1, y2);
    }
    int xmin() const {
        return std::min(x1, x2);
    }
    int xmax() const {
        return std::max(x1, x2);
    }
    int length() const {
        return std::max(xmax() - xmin(), ymax() - ymin());
    }
};

struct Grid {
    int** counts;
    int xmax;
    int ymax;

    Grid(const std::vector<Line> &lines) {
        xmax = std::accumulate(lines.begin(), lines.end(), 0, [](auto &a, auto &b) {
            return std::max(std::max(a, b.x2), b.x1);
        });
        ymax = std::accumulate(lines.begin(), lines.end(), 0, [](auto &a, auto &b) {
            return std::max(std::max(a, b.y2), b.y1);
        });
        printf("xmax/ymax : %d / %d\n", xmax, ymax);

        counts = new int*[ymax + 1];
        for (int i = 0; i <= ymax; i++) {
            counts[i] = new int[xmax + 1]();
        }
        for (auto& line : lines) {
            if (line.diagonal()) {
                for (int i = 0; i <= line.length(); i++) {
                    bool xasc = line.x2 > line.x1;
                    bool yasc = line.y2 > line.y1;
                    counts[line.y1 + (yasc ? i : -i)][line.x1 + (xasc ? i : -i)]++;
                }
            } else {
                if (line.x1 != line.x2) {
                    for (int i = line.xmin(); i <= line.xmax(); i++) {
                        counts[line.y1][i]++;
                    }
                } else {
                    for (int i = line.ymin(); i <= line.ymax(); i++) {
                        counts[i][line.x1]++;
                    }
                }   
            }
        }
    }

    long count_larger_than(int count) const {
        long sum = 0;
        for (int i = 0; i <= ymax; i++) {
            for (int j = 0; j <= xmax; j++) {
                if (counts[i][j] > count) {
                    sum++;
                }
            }
        }
        return sum;
    }

    void print() const {
        std::cout << std::endl;
        for (int i = 0; i <= ymax; i++) {
            for (int j = 0; j <= xmax; j++) {
                std::cout << counts[i][j] << " "; 
            }
            std::cout << std::endl;
        }
    }
};

int main(int argc, char** argv) {
    std::ifstream input("p5.txt");
    std::string line;
    std::vector<Line> lines;
    while (std::getline(input, line)) {
        int x1, x2, y1, y2;
        int count = std::sscanf(line.c_str(), "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
        assert(count == 4);
        lines.push_back({x1, x2, y1, y2});
    }
    std::cout << "Parsed " << lines.size() << " lines" << std::endl;
    Grid grid(lines);
    // grid.print();

    std::cout << grid.count_larger_than(1) << std::endl;
    return 0;
}
