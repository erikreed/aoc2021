#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <string>
#include <numeric>
#include <cmath>
#include <map>
#include <algorithm>


int main(int argc, char** argv) {
    std::ifstream input("p6.txt");
    std::string part;
    std::vector<int> numbers;
    while (std::getline(input, part, ',')) {
        numbers.push_back(atoi(part.c_str()));
    }
    std::cout << numbers.size() << std::endl;

    std::map<int, long> days_remaining_to_fish_count;

    for (int n : numbers) {
        days_remaining_to_fish_count[n] += 1;
    }

    const int NUM_DAYS = 256;
    for (int day = 0; day < NUM_DAYS; day++) {
        long fish_at_zero = days_remaining_to_fish_count[0];
        days_remaining_to_fish_count[0] = 0;

        for (int days_remaining = 1; days_remaining <= 8; days_remaining++) {
            long num_fish = days_remaining_to_fish_count[days_remaining];
            days_remaining_to_fish_count[days_remaining] = 0;
            days_remaining_to_fish_count[days_remaining - 1] += num_fish;
        }

        days_remaining_to_fish_count[8] += fish_at_zero;
        days_remaining_to_fish_count[6] += fish_at_zero;
    }
    long fish_count = 0;
    for (auto &item : days_remaining_to_fish_count) {
        printf("Fish: %d, %ld\n", item.first, item.second);

        fish_count += item.second;
    }
    printf("Fish count %ld\n", fish_count);

    return 0;
}
