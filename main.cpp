/* 
 * File:   main.cpp
 * Author: Alberto García
 *
 * Created on 20th February, 2017, 14:16
 */

// Libraries and headers.
#include <iostream> // Basic library for console.
#include <cstdlib> // For rand.
#include <ctime> // For having a date (as initial seed for rand).

// Global variables (bad, but useful idea here)
const int g_SLOTS=3; // Slots for each round.
const int g_SYMBOLS=5; // Different values we can get.
const int g_COST=1; // "Price" for each round-

// Functions

// Row prize checker.
int f_rows (int array[][g_SLOTS]) {
    int row_reward = 0; // I need to return a value to main.
    for (int a = 0; a < g_SLOTS; a++) { // For each row in the slot machine.
        int reward_checker = 0; // Log of equalities between symbols.
        for (int b = 0; b < g_SLOTS - 1; b++) { // Check each slot.
            if (array[a][b] == array[a][b+1]) {
                reward_checker = reward_checker + 1;
            }
        }
        if (reward_checker == g_SLOTS - 1) {
            row_reward = row_reward + array[a][0]; // Just a log for the reward.
        }
    }
    return row_reward;
}

// Column reward checker.
int f_columns (int array[][g_SLOTS]) {
    int column_reward = 0; // I need to return a value to main.
    for (int a = 0; a < g_SLOTS; a++) { // For each column in the slot machine.
        int reward_checker = 0; // Log of equalities between symbols.
        for (int b = 0; b < g_SLOTS - 1; b++) { // Check each slot.
            if (array[b][a] == array[b+1][a]) {
                reward_checker = reward_checker + 1;
            }
        }
        if (reward_checker == g_SLOTS - 1) {
            column_reward = column_reward + array[0][a];
        }
    }
    return column_reward;
}

// Main diagonal reward checker.
int f_mdiagonal (int array[][g_SLOTS]) {
    int mdiagonal_reward = 0; // I need to return a value to main.
    int reward_checker = 0; // Log of equalities between symbols.
    for (int a = 0; a < g_SLOTS - 1; a++) { // If I'm in range of the matrix.
        if (array[a][a] == array[a+1][a+1]) { // Diagonal checker.
            reward_checker = reward_checker + 1;
        }
        if (reward_checker == g_SLOTS - 1) {
            mdiagonal_reward = mdiagonal_reward + array[0][0];
        }
    }
    return mdiagonal_reward;
}

// Secondary diagonal reward checker.
int f_sdiagonal (int array[][g_SLOTS]){
    int sdiagonal_reward = 0; // I need to return a value to main.
    int reward_checker = 0; // Log of equalities between symbols.
    for (int a = g_SLOTS-1; 0 < a; a--) {
        // Sum must be a + b = g_SLOTS - 1 
        if (array[a][g_SLOTS-1-a] == array[a-1][g_SLOTS-a]) {
            reward_checker = reward_checker + 1;
        }
        if (reward_checker == g_SLOTS - 1) {
            sdiagonal_reward = sdiagonal_reward + array[g_SLOTS-1][0];
        }
    }
    return sdiagonal_reward;
}

/*
 * Let's make this a bit more complicated: each round is stored as a 2D, 3x3-matrix
 * and they are 9 arranged values. Now, reward checks are done by row, column and
 * both main and secondary diagonals
 *  */

int main(int argc, char** argv) {
    // Here I have a squared array.
    int results[g_SLOTS][g_SLOTS];
    // Let's explain some variables a little.
    int money = 0; // Money the player "invests".
    int r_reward = 0; // Tokens rewarded on each round.
    int r_chest = 0; // Tokens saved along rounds.
    int total = 0; // Total rounds played.
    // Some text variables to control user input.
    char answer[2] = "y"; // To keep playing (or not).
    char addprize[2] = "y"; // To add rewards to get more rounds (or not).
    
    // A bit of text on screen, to make it user-friendly.
    std::cout << "Welcome to this slot machine.\n";
    std::cout << "How much money you want to play?: ";
    std::cin >> money;
    std::cout << "We'll play, at least, " << money/g_COST << " rounds.\n\n";

    
    // I start the RNG.
    srand(time(NULL));
    // This while is to control if the player wants to keep playing.
    while ((answer[0] == 'y')||(answer[0] == 'Y')) {
        if (money >= 1) {
            money = money - g_COST; // I take a round.
            total = total + 1;
            r_reward = 0; // I reset the reward.
    
            // I fill and display a matrix (I avoid a loop).
            for (int a = 0; a < g_SLOTS; a++) { // This stands for rows.
                for (int b = 0; b < g_SLOTS; b++) { // And this for columns.
                    results[a][b] = std::rand() % g_SYMBOLS + 1;
                    std::cout << results[a][b] << " ";
                }
                std::cout << "\n";
            }
            std::cout << "\n";
    
            // I'm pretty sure I can do this with pointers. Maybe later.
            // Row checks.
            r_reward = r_reward + f_rows(results);
    
            // Column checks.
            r_reward = r_reward + f_columns(results);
            
            // Main diagonal check.
            r_reward = r_reward + f_mdiagonal(results);
            
            // Secondary diagonal check.
            r_reward = r_reward + f_sdiagonal(results);

            
            // I add the rewards and display together at the end.
            if (r_reward != 0) {
                std::cout << "You won! Your reward is " << r_reward << "$.\n\n";
                std::cout << "Do you want to add the reward to get more rounds?: ";
                std::cin >> addprize;
                if ((addprize[0] == 'y')||(addprize[0] == 'Y')) {
                    money = money + r_reward;
                } else {
                    r_chest = r_chest + r_reward; // If not, rewards are stored.
                }
            } else { // In case I have no luck.
                std::cout << "Try again.\n\n";
            }
            // Now, to know if I can keep playing...
            std::cout << "You still have " << money/g_COST << " rounds.\n";
            std::cout << "Your saved reward is " << r_chest << "$.\n";
            std::cout << "Do you want to play another round? (y/n): ";
            std::cin >> answer;
            std::cout << std::endl;
        } else {
            std::cout << "Sorry, you have no rounds left.\n\n";
            answer[0]='n';
            // What if I want to add saved rewards to keep playing?
            // Or if I want to take my remaining money?
        }
    }
    
    // Program's end, data summary.
    std::cout << "At the end of the game,\n you have played " << total << " rounds\n";
    std::cout << "and your total reward is " << r_chest << "$.\n";
        
    return 0;
}