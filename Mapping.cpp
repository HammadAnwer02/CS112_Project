#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

class myMapping // converts the data from the training text file into integers
{
    map<string, int> mapping{
        {"o", 2},
        {"x", 1},
        {"b", 0},
        {"positive", 3},
        {"negative", -1}};

    vector<string> input;
    vector<vector<string>> input1; // 2D vector to hold data from the file
    static int num;

public:
    void reading_value() // reads all the values from the file and stores them in the string vector "input"
    {
        ifstream in{"tic-tac-toe.txt"};
        string temp;
        while (getline(in, temp))
        {
            input.push_back(temp);
            num++; // keeps count of the number of inputs
        }
    }

    void print_vec()
    {
        for (int i = 0; i < input1.size(); i++)
        {
            for (int j = 0; j < input1[i].size(); j++)
            {
                cout << input1[i][j] << " ";
            }
            cout << endl;
        }
    }

    void output_values() // outputs all the values form the vector string onto the updated file
    {
        ofstream out{"updated-tictactoe.txt"};
        int count = 0;             // to track the current index of a tokenized string
        int InputCount = 0;        // to track the current index of the vector
        vector<string> tempinput;  // temp variable to print mapped data in file
        vector<string> tempinput2; // temp variable to print mapped data in 2D vector
        int x;                     // mapped value of tokenized string
        while (InputCount != num)
        {
            tempinput = tokenize(input[InputCount]);
            input1.push_back(tempinput);

            for (int j = 0; j < tempinput.size(); j++)
            {
                int x = mapping[tempinput[j]];
                out << x << ",";
                count++;
                if (count % 10 == 0)
                {
                    out << endl;
                }
            }
            InputCount++;
        }
    }
    vector<string> tokenize(string x) // tokenizes each string stored int the vector "input"
    {

        vector<string> tokens;

        stringstream strinput(x);

        string temp;

        int count = 0;
        while (getline(strinput, temp, ','))
        {
            tokens.push_back(temp);
            count++;
            if (count == 10)
            {
                getline(strinput, temp, '\n');
                count = 0;
            }
        }
        return tokens;
    }
};

int myMapping::num = 0;

int main()
{
    myMapping m1;
    m1.reading_value();
    m1.output_values();
    m1.print_vec();
}
