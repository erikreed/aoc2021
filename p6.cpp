#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>
#include <fstream>
#include <string>
#include <numeric>
#include <cmath>
#include <algorithm>


class FishSquad {
public:
    int days_remaining;
    long quantity;

    FishSquad(int days_remaining = 8, long quantity = 1) {
        this->days_remaining = days_remaining;
        this->quantity = quantity;
    }

    bool pass_day() {
        days_remaining--;
        if (days_remaining < 0) {
            days_remaining = 6;
            return true;
        }
        return false;
    }
};

int main(int argc, char** argv) {
    std::ifstream input("p6.txt");
    std::string part;
    std::vector<int> numbers;
    while (std::getline(input, part, ',')) {
        numbers.push_back(atoi(part.c_str()));
    }
    std::cout << numbers.size() << std::endl;

    std::vector<FishSquad> fish_tank;

    for (int n : numbers) {
        fish_tank.push_back(FishSquad(n));
    }

    const int NUM_DAYS = 256;
    for (int i = 0; i < NUM_DAYS; i++) {
        printf("Day %d\n", i);
        std::vector<FishSquad> new_fish_tank;
        for (FishSquad &fish : fish_tank) {
            bool spawned = fish.pass_day();
            
            if (spawned) {
                new_fish_tank.push_back(FishSquad());
            }
        }
        fish_tank.insert(fish_tank.end(), new_fish_tank.begin(), new_fish_tank.end());


        printf("Num fish squads: %lu\n", fish_tank.size());
    }
    printf("Num fishes: %lu\n", fish_tank.size());

    return 0;
}
