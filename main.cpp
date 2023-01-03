#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

#include "Qlearning.h"


class TicTacToe {
    public:
        TicTacToe();
        void play();
        // int move();
        void printBoard();
        bool CheckWin(char sign);
    private:
        char board[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
        bool player1;
};

TicTacToe::TicTacToe() {
    player1 = true;
}

void TicTacToe::printBoard() {
    std::cout << "_____________" << std::endl;
    for (int i=0; i < 9; i++) {
        if (i == 0) {
            std::cout << "| ";
        } else if (i == 3) {
            std::cout << std::endl;
            std::cout << "| ";
        } else if (i == 6) {
            std::cout << std::endl;
            std::cout << "| ";
        }
        std::cout << board[i] << " | ";
    }
    std::cout << std::endl;
    std::cout << "-------------" << std::endl;
    std::cout << std::endl;
}

void TicTacToe::play() {
    Qlearning Qtable;
    bool door = true;
    while(door) {
        if (player1) {
            bool notplaced = true;
            std::vector<char> boardvec1;
            for (int i=0; i < 9; i++) {
                boardvec1.push_back(board[i]);
            }
            while (notplaced) {
                int choice = Qtable.makeDecision(&boardvec1);
                if (board[choice] == '-') {
                    notplaced = false;
                    board[choice] = 'X';
                }
            }
            player1 = false;
            Qtable.saveQtable();

            int reward;
            if (CheckWin('X')) {
                reward = 100;
                door = false;
            } else {
                reward = 10;
            }
            std::vector<char> boardvec;
            for (int i=0; i < 9; i++) {
                boardvec.push_back(board[i]);
            }
            // Qtable.Reward(&boardvec, reward);
        } else {
            bool notplaced = true;
            std::vector<char> boardvec1;
            for (int i=0; i < 9; i++) {
                boardvec1.push_back(board[i]);
            }
            while (notplaced) {
                int choice = Qtable.makeDecision(&boardvec1);
                if (board[choice] == '-') {
                    notplaced = false;
                    board[choice] = 'O';
                }
            }
            player1 = true;
            Qtable.saveQtable();

            int reward;
            if (CheckWin('O')) {
                reward = 100;
                door = false;
            } else {
                reward = 10;
            }
            std::vector<char> boardvec;
            for (int i=0; i < 9; i++) {
                boardvec.push_back(board[i]);
            }
        }
        printBoard();
        int placesLeft = 0;
        for (int i=0; i < 9; i++) {
            if (board[i] == '-') {
                placesLeft++;
            }
        }
        if (placesLeft == 0) {
            door = false;
        }
    }
    Qtable.saveQtable();
}

bool TicTacToe::CheckWin(char sign) {
    if ((board[0] == sign && board[1] == sign && board[2] == sign) || (board[3] == sign && board[4] == sign && board[5] == sign) 
    || (board[6] == sign && board[7] == sign && board[8] == sign) || (board[0] == sign && board[3] == sign && board[6] == sign) 
    || (board[1] == sign && board[4] == sign && board[7] == sign) || (board[2] == sign && board[5] == sign && board[8] == sign)
    || (board[0] == sign && board[4] == sign && board[9] == sign) || (board[2] == sign && board[4] == sign && board[7] == sign)) {
        return true;
    } else {
        return false;
    }
}

int main() {
    srand(time(NULL));
    TicTacToe spel;
    spel.printBoard();
    spel.play();
    
    return 0;
}