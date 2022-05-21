#include <iostream>
#include "TicTacToe.h"

using namespace std;

TicTacToe::TicTacToe()
{
}

void TicTacToe::showBoard()
{
    system("cls");
    cout << "\n\n\tTic Tac Toe\n\n";

    cout << "Player 1 (X)  -  Player 2 (O)" << endl
         << endl;
    cout << endl;

    cout << "     |     |     " << endl;
    cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << endl;

    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;

    cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << endl;

    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;

    cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << endl;

    cout << "     |     |     " << endl
         << endl;
}

bool TicTacToe::isDraw()
{
    return (board[0] != '1' && board[1] != '2' && board[2] != '3' && board[3] != '4' && board[4] != '5' && board[5] != '6' && board[6] != '7' && board[7] != '8' && board[8] != '9');
}
int TicTacToe::checkwin()
{
    if (board[1] == board[2] && board[2] == board[3])

        return 1;
    else if (board[4] == board[5] && board[5] == board[6])

        return 1;
    else if (board[7] == board[8] && board[8] == board[9])

        return 1;
    else if (board[1] == board[4] && board[4] == board[7])

        return 1;
    else if (board[2] == board[5] && board[5] == board[8])

        return 1;
    else if (board[3] == board[6] && board[6] == board[9])

        return 1;
    else if (board[1] == board[5] && board[5] == board[9])

        return 1;
    else if (board[3] == board[5] && board[5] == board[7])

        return 1;
    else if (isDraw())
        return 0;
    else
        return -1;
}

void TicTacToe::makeMove()
{
    int player = 1;
    int i, choice;

    char mark;
    do
    {
        showBoard();
        player = (player % 2) ? 1 : 2;

        cout << "Player " << player << ", enter a number:  ";
        cin >> choice;

        mark = (player == 1) ? 'X' : 'O';

        if (choice == 1 && board[0] == '1')

            board[0] = mark;
        else if (choice == 2 && board[1] == '2')

            board[1] = mark;
        else if (choice == 3 && board[2] == '3')

            board[2] = mark;
        else if (choice == 4 && board[3] == '4')

            board[3] = mark;
        else if (choice == 5 && board[4] == '5')

            board[4] = mark;
        else if (choice == 6 && board[5] == '6')

            board[5] = mark;
        else if (choice == 7 && board[6] == '7')

            board[6] = mark;
        else if (choice == 8 && board[7] == '8')

            board[7] = mark;
        else if (choice == 9 && board[8] == '9')

            board[8] = mark;
        else
        {
            cout << "Invalid move ";

            player--;
            cin.ignore();
            cin.get();
        }
        i = checkwin();

        player++;
    } while (i == -1);
    showBoard();
    if (i == 1)

        cout << "==>\aPlayer " << --player << " win ";
    else
        cout << "==>\aGame draw";
}

vector<double> TicTacToe::getBoardState() {
    vector<double> temp;
    for (int i = 0; i < 9; i++) {
        temp.push_back(static_cast<double>(board[i]));
    }
    return temp;
}
