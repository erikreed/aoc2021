#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <sstream>
#include <string>

using namespace std;

class Board {
private:
    vector<int> numbers;
    bool** marked;
public:
    Board(vector<int> numbers) : numbers(numbers) {
        assert(numbers.size() == 25);
        marked = new bool*[5];
        
        for (int i = 0; i < 5; i++) {
            marked[i] = new bool[5]();
        }
    }

    int sum_unmarked() {
        int sum = 0;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (!marked[i][j]) {
                    sum += at(i, j);
                }
            }
        }
        return sum;
    }

    void mark(int number) {
        
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (at(i, j) == number) {
                    marked[i][j] = true;
                    // print_marked();
                }
            }
        }
    }

    bool complete() {
        for (int row = 0; row < 5; row++) {
            bool found = true;
            for (int col = 0; col < 5; col++) {
                if (!marked[row][col]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return true;
            }
        }

        for (int col = 0; col < 5; col++) {
            bool found = true;
            for (int row = 0; row < 5; row++) {
                if (!marked[row][col]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                return true;
            }
        }

        return false;
    }

    int& at(int i, int j) {
        int idx = i * 5 + j;
        assert(0 <= idx && idx < 25);
        return numbers[idx];
    }

    void print() {
        cout << endl;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (marked[i][j]) {
                    cout << " X ";
                } else {
                    auto next = at(i, j);
                    cout << next << " ";
                    if (next < 10) cout << " ";
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    void print_marked() {
        cout << endl;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                cout << marked[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};

int main(int argc, char** argv) {
    ifstream file("p4.txt");

    string header;
    file >> header;

    vector<Board*> boards;
    vector<int> numbers;
    int n;
    while (file >> n) {
        numbers.push_back(n);

        if (numbers.size() == 25) {
            boards.push_back(new Board(numbers));
            numbers.clear();
        }
    }

    // -----------------------------

    stringstream header_stream(header);
    
    std::string token;

    Board* winner = nullptr;
    int last = -1;
    while(getline(header_stream, token, ',')) {
        n = stoi(token);
        for (Board* b : boards) {
            if (!b->complete()) {
                b->mark(n);
                if (b->complete()) {
                    winner = b;
                    last = n;
                }
            }
            
        }
    }

    cout << header << endl;

    cout << winner->sum_unmarked() * last << endl;

    return 1;
}