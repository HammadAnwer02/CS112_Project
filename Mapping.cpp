#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

class myMapping
{
    map<string, int> mapping{
        {"o", 2},
        {"x", 1},
        {"b", 0},
        {"positive", 3},
        {"negative", -1}};

    vector<string> input;
    static int num;

public:
    void reading_value()
    {
        ifstream in{"tic-tac-toe.txt"};
        string temp;
        while (getline(in, temp))
        {
            input.push_back(temp);
            num++;
        }
    }

    void output_values()
    {
        ofstream out{"updated-tictactoe.txt"};
        int count = 0;
        int InputCount = 0;
        vector<string> tempinput;
        while (InputCount != num)
        {
            tempinput = tokenize(input[InputCount]);
            for (int i = 0; i < tempinput.size(); i++)
            {
                if (i != tempinput.size() - 1)
                {
                    out << mapping[tempinput[i]] << ",";
                }
                else
                {
                    out << mapping[tempinput[i]];
                }
                count++;
                if (count % 10 == 0)
                {
                    out << endl;
                }
            }
            InputCount++;
        }
    }

    vector<string> tokenize(string x)
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
}
