/**
 * @file TicTacToe.cpp
 * @author M.Arsal 2021355
 * @brief Stores the implementation of the TicTacToe Class
 * @version 0.1
 * @date 2022-05-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include <iostream>
#include "TicTacToe.h"
#include "Mapping.h"
#include <chrono>
#include <thread>


using namespace std;
// these are just there to add pause to our code
using namespace std::this_thread;     
using namespace std::chrono_literals; 
using std::chrono::system_clock;

TicTacToe::TicTacToe()
{
}

void TicTacToe::showBoard() // display board
{
    system("cls");
    cout << "\n\n\tTic Tac Toe\n\n";

    cout << "Player 1 (X) You -  Player 2 (O) The Computer" << endl
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

bool TicTacToe::isDraw() // check is game has been drawn
{
    return (board[0] != '1' && board[1] != '2' && board[2] != '3' && board[3] != '4' && board[4] != '5' && board[5] != '6' && board[6] != '7' && board[7] != '8' && board[8] != '9');
}
int TicTacToe::checkwin() // check if any player has won
{
    if (board[0] == board[1] && board[1] == board[2])

        return 1;
    else if (board[3] == board[4] && board[4] == board[5])

        return 1;
    else if (board[6] == board[7] && board[7] == board[8])

        return 1;
    else if (board[0] == board[3] && board[3] == board[6])

        return 1;
    else if (board[1] == board[4] && board[4] == board[7])

        return 1;
    else if (board[2] == board[5] && board[5] == board[8])

        return 1;
    else if (board[0] == board[4] && board[4] == board[8])

        return 1;
    else if (board[2] == board[4] && board[4] == board[6])

        return 1;
    else if (isDraw())
        return 0;
    else
        return -1;
}

bool TicTacToe::placemark(int choice, char mark) // change board state after move has been done
{

    if (isEmpty(choice - 1))
    {
        board[choice - 1] = mark;

        return true;
    }
    else
    {
        cout << "This position is not empty!";
        sleep_for(3s);
        return false;
    }
}

bool TicTacToe::isEmpty(int index)
{
    //mapping just to check if the board place is empty
    map<int, char> mappos = {
        {0, '1'},
        {1, '2'},
        {2, '3'},
        {3, '4'},
        {4, '5'},
        {5, '6'},
        {6, '7'},
        {7, '8'},
        {8, '9'}};
    
    if (board[index] == mappos[index])
    {
        return true;
    }
    else
    {
        return false;
    }
}

// computer will decide which move to make
int TicTacToe::computeMove(Net &myNet)
{
    default_random_engine engine{static_cast<unsigned>(time(0))};
    uniform_int_distribution<int> randomint{0,2};
    double least = 1000;
    double result;
    int indexOfLeast;
    for (int i = 0; i < 9; i++)
    {   
        if (isEmpty(i))
        {
            vector<double> temp = getBoardState();
            temp[i] = 0.5;
            for (int j = 0; j < temp.size(); j++) {
                if (j != i) {
                    temp[j] = randomint(engine);
                }
            }
            myNet.forwardPropogation(temp);
            vector<double> resultVals;
            myNet.getResult(resultVals);

            result = resultVals[0];
    
            if ((result < least))
            {
                least = result;
                indexOfLeast = i;
            }
        }
    }

    return indexOfLeast;
}

// start the game
void TicTacToe::play(Net &myNet)
{
    
    int player = 1;
    int i, choice;

    char mark;
    do
    {
        showBoard();
        player = (player % 2) ? 1 : 2;

        mark = (player == 1) ? 'X' : 'O'; // check what to play based on who has the move at the moment
        if (player == 1)
        {
            cout << "Player " << player << ", enter a number:  ";
            cin >> choice;
            if (!placemark(choice, mark))
            {
                cout << "Invalid move ";
                player--;
                cin.ignore();
                cin.get();
            }
        }
        else
        {
            cout << "Computer is Making its move ";
            for (int i = 0; i< 5; i++) {
                cout << ". ";
                sleep_for(500ms);
            }
            cout << endl;
            int choice = computeMove(myNet);
            if (!placemark(choice + 1, mark))
            {
                cout << "Invalid Move";
                player--;
            }
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

// return the board state
vector<double> TicTacToe::getBoardState()
{
    vector<double> temp;
    for (int i = 0; i < 9; i++)
    {
        temp.push_back(static_cast<double>(board[i]));
    }
    return temp;
}
