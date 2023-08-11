#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

bool solveCryptarithmetic(std::string& puzzle, std::vector<int>& assignment, std::vector<bool>& used, int currentLetter) {
    if (currentLetter == puzzle.length()) {
        int num1 = 1000 * assignment[puzzle[0] - 'A'] + 100 * assignment[puzzle[1] - 'A'] +
                   10 * assignment[puzzle[2] - 'A'] + assignment[puzzle[3] - 'A'];
        int num2 = 1000 * assignment[puzzle[5] - 'A'] + 100 * assignment[puzzle[6] - 'A'] +
                   10 * assignment[puzzle[7] - 'A'] + assignment[puzzle[8] - 'A'];
        int sum = 10000 * assignment[puzzle[10] - 'A'] + 1000 * assignment[puzzle[11] - 'A'] +
                  100 * assignment[puzzle[12] - 'A'] + 10 * assignment[puzzle[13] - 'A'] +
                  assignment[puzzle[14] - 'A'];

        return (num1 + num2 == sum);
    }

    if (assignment[puzzle[currentLetter] - 'A'] != -1)
        return solveCryptarithmetic(puzzle, assignment, used, currentLetter + 1);

    for (int digit = 0; digit <= 9; digit++) {
        if (!used[digit]) {
            used[digit] = true;
            assignment[puzzle[currentLetter] - 'A'] = digit;
            if (solveCryptarithmetic(puzzle, assignment, used, currentLetter + 1))
                return true;
            used[digit] = false;
            assignment[puzzle[currentLetter] - 'A'] = -1;
        }
    }

    return false;
}

int main() {
    std::string puzzle = "SEND + MORE = MONEY";
    std::vector<int> assignment(26, -1);  // Vector to store digit assignments
    std::vector<bool> used(10, false);    // Vector to keep track of used digits

    if (solveCryptarithmetic(puzzle, assignment, used, 0)) {
        std::cout << "Solution found:" << std::endl;
        std::cout << puzzle << std::endl;
        std::cout << "Digits assignment:" << std::endl;
        for (int i = 0; i < 26; i++) {
            if (assignment[i] != -1)
                std::cout << char('A' + i) << ": " << assignment[i] << std::endl;
        }
    } else {
        std::cout << "No solution found for the given puzzle." << std::endl;
    }

    return 0;
}
