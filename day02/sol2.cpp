#include <bits/stdc++.h>
using namespace std;
int main()
{
    int total = 0;
    char opp;
    char you;
    while (cin >> opp >> you)
    {

        int score = you == 'X' ? 0 : you == 'Y' ? 3
                                                : 6;

        if (opp == 'B' && you == 'X' || opp == 'A' && you == 'Y' || opp == 'C' && you == 'Z')
        {
            score += 1;
        }
        else if (opp == 'C' && you == 'X' || opp == 'B' && you == 'Y' || opp == 'A' && you == 'Z')
        {
            score += 2;
        }
        else
        {
            score += 3;
        }

        total += score;
    }
    cout << total << endl;
}