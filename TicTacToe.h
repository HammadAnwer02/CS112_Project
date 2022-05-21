#pragma once

#include <iostream>
#include <vector>

using namespace std;

class TicTacToe
{
public:
    TicTacToe();
    int checkwin();
    void showBoard();
    void makeMove();
    bool isDraw();
    vector<double> getBoardState();

private:
    char board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
};