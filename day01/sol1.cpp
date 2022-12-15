#include <iostream>
#include <string>
using namespace std;
int main()
{
    int cur_max = -1;
    int cur_sum = 0;
    string input;
    while (!cin.eof())
    {
        getline(cin, input);
        if (input.empty())
        {
            cur_max = max(cur_sum, cur_max);
            cur_sum = 0;
        }
        else
        {
            int cur = stoi(input);
            cur_sum += cur;
        }
    }
    cout << cur_max << endl;
}