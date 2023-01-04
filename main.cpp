#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>

#include "Qlearning.h"


class TicTacToe {
    public:
        TicTacToe();
        void play();
        void restartBoard();
        // int move();
        void printBoard();
        bool CheckWin(char sign);

        int winsP1;
        int winsP2;
        Qlearning Qtable;
    private:
        char board[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
        bool player1;
        int rewardP1, rewardP2;
        std::vector<std::vector<char>> statesP1, statesP2;
        std::vector<int>  actionsP1, actionsP2;
};

TicTacToe::TicTacToe() {
    player1 = true;
    winsP1 = 0;
    winsP2 = 0;
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

void TicTacToe::restartBoard() {
    for (int i=0; i < 9; i++) {
        board[i] = '-';
    }
}

void TicTacToe::play() {
    bool door = true;
    statesP1.clear();
    statesP2.clear();
    actionsP1.clear();
    actionsP2.clear();
    while(door) {
        if (player1) {
            bool notplaced = true;
            std::vector<char> boardvec1;
            for (int i=0; i < 9; i++) {
                boardvec1.push_back(board[i]);
            }
            statesP1.push_back(boardvec1);
            int choice;
            while (notplaced) {
                choice = Qtable.makeDecision(&boardvec1);
                if (board[choice] == '-') {
                    notplaced = false;
                    board[choice] = 'X';
                }
            }
            actionsP1.push_back(choice);
            player1 = false;
            Qtable.saveQtable();

            if (CheckWin('X')) {
                rewardP1 = 100;
                rewardP2 = -100;
                winsP1++;
                door = false;
            }

            std::vector<char> boardvec;
            for (int i=0; i < 9; i++) {
                boardvec.push_back(board[i]);
            }
        } else {
            bool notplaced = true;
            std::vector<char> boardvec1;
            for (int i=0; i < 9; i++) {
                boardvec1.push_back(board[i]);
            }
            statesP2.push_back(boardvec1);
            int choice;
            while (notplaced) {
                choice = Qtable.makeDecision(&boardvec1);
                if (board[choice] == '-') {
                    notplaced = false;
                    board[choice] = 'O';
                }
            }
            actionsP2.push_back(choice);
            player1 = true;
            Qtable.saveQtable();

            int reward;
            if (CheckWin('O')) {
                rewardP2 = 100;
                rewardP1 = -100;
                winsP2++;
                door = false;
            }
            
            std::vector<char> boardvec;
            for (int i=0; i < 9; i++) {
                boardvec.push_back(board[i]);
            }
        }
        // printBoard();
        int placesLeft = 0;
        for (int i=0; i < 9; i++) {
            if (board[i] == '-') {
                placesLeft++;
            }
        }
        if (placesLeft == 0) {
            door = false;
            rewardP1 = 10;
            rewardP2 = 10;
        }
    }
    Qtable.saveQtable();
    for (int i=0; i < statesP1.size(); i++) {
        Qtable.Reward(&statesP1.at(i), rewardP1, actionsP1.at(i));
    }
    for (int i=0; i < statesP2.size(); i++) {
        Qtable.Reward(&statesP2.at(i), rewardP2, actionsP2.at(i));
    }
    Qtable.saveQtable();
}

bool TicTacToe::CheckWin(char sign) {
    if ((board[0] == sign && board[1] == sign && board[2] == sign) || (board[3] == sign && board[4] == sign && board[5] == sign) 
    || (board[6] == sign && board[7] == sign && board[8] == sign) || (board[0] == sign && board[3] == sign && board[6] == sign) 
    || (board[1] == sign && board[4] == sign && board[7] == sign) || (board[2] == sign && board[5] == sign && board[8] == sign)
    || (board[0] == sign && board[4] == sign && board[8] == sign) || (board[2] == sign && board[4] == sign && board[6] == sign)) {
        return true;
    } else {
        return false;
    }
}

int main() {
    srand(time(NULL));
    TicTacToe spel;
    spel.printBoard();
    float epsilon = 1;
    for (int i=0; i < epsilon; epsilon-=0.1) {
        for (int i=0; i < 1000; i++) {
            spel.play();
            spel.restartBoard();
        }
        // epsilon -= 0.1;
        std::cout << spel.winsP1 << " wins player 1 " << spel.winsP2 << " wins player 2 " << 1000-spel.winsP1-spel.winsP2 << " draw " << std::endl;
        spel.winsP1 = 0;
        spel.winsP2 = 0;
        spel.Qtable.SetEpsilon(epsilon);
    }
    spel.Qtable.SetEpsilon(1);
    for (int i=0; i < 5000; i++) {
        spel.play();
        spel.restartBoard();
    }
    std::cout << spel.winsP1 << " wins player 1 " << spel.winsP2 << " wins player 2 " << 1-spel.winsP1-spel.winsP2 << " draw " << std::endl;
    return 0;
}