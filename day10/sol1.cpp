#include <bits/stdc++.h>
using namespace std;
int main()
{
    int value = 1;
    int target = 20;
    int sum = 0;

    string command;
    int signal;
    bool skip = false;
    for (int current = 1; current <= 220; current++)
    {
        if (current == target)
        {
            sum += current * value;
            target += 40;
            // cout << "cycle " << current << ": " << value << endl;
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
    cout << sum << endl;
}
