#include <bits/stdc++.h>
using namespace std;
int main()
{
    int value = 1;
    int target = 20;
    char crt[6][40];

    string command;
    int signal;
    bool skip = false;
    for (int row = 0; row < 6; row++)
    {
        for (int pixel = 0; pixel < 40; pixel++)
        {
            if (value - 1 <= pixel && pixel <= value + 1)
            {
                crt[row][pixel] = '#';
            }
            else
            {
                crt[row][pixel] = '.';
            }
            if (!skip)
            {
                cin >> command;
                if (command == "addx")
                {
                    cin >> signal;
                    skip = true;
                }
            }
            else
            {
                value += signal;
                skip = false;
            }
        }
    }

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            cout << crt[i][j];
        }
        cout << endl;
    }
}
