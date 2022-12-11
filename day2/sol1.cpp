#include <bits/stdc++.h>
using namespace std;
int main()
{
    int total = 0;
    char opp;
    char you;
    while (cin >> opp >> you)
    {

        int score = you == 'X' ? 1 : you == 'Y' ? 2
                                                : 3;
        if (opp == 'A' && you == 'Y' || opp == 'B' && you == 'Z' || opp == 'C' && you == 'X')
        {
            score += 6;
        }
        else if (opp == 'A' && you == 'X' || opp == 'B' && you == 'Y' || opp == 'C' && you == 'Z')
        {
            score += 3;
        }
        total += score;
    }
    cout << total << endl;
}