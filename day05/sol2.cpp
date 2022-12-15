#include <bits/stdc++.h>
using namespace std;
int main()
{
    // lazy to parse the drawing, so i just transcribed it
    /*
        [P]                 [Q]     [T]
    [F] [N]             [P] [L]     [M]
    [H] [T] [H]         [M] [H]     [Z]
    [M] [C] [P]     [Q] [R] [C]     [J]
    [T] [J] [M] [F] [L] [G] [R]     [Q]
    [V] [G] [D] [V] [G] [D] [N] [W] [L]
    [L] [Q] [S] [B] [H] [B] [M] [L] [D]
    [D] [H] [R] [L] [N] [W] [G] [C] [R]
     1   2   3   4   5   6   7   8   9
    */
    string s[10];
    s[1] = "DLVTMHF";
    s[2] = "HQGJCTNP";
    s[3] = "RSDMPH";
    s[4] = "LBVF";
    s[5] = "NHGLQ";
    s[6] = "WBDGRMP";
    s[7] = "GMNRCHLQ";
    s[8] = "CLW";
    s[9] = "RDLQJZMT";

    stack<char> stacks[10];
    for (int i = 1; i < 10; i++)
    {
        for (char c : s[i])
        {
            stacks[i].push(c);
        }
    }
    int num;
    int source;
    int target;
    int tmp;
    string dummy;
    while (cin >> dummy >> num >> dummy >> source >> dummy >> target)
    {
        for (int j = 0; j < num; j++)
        {
            tmp = stacks[source].top();
            stacks[source].pop();
            stacks[0].push(tmp);
        }
        while (!stacks[0].empty())
        {
            tmp = stacks[0].top();
            stacks[0].pop();
            stacks[target].push(tmp);
        }
    }
    for (int k = 1; k < 10; k++)
    {
        cout << stacks[k].top();
    }
    cout << endl;
}
