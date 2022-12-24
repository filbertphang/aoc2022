#include <bits/stdc++.h>
using namespace std;

// converts from a item to its priority
int get_item_prio(char item)
{
    int num = (int)item;
    if (num >= 97)
    {
        return num - 96;
    }
    else
    {
        return num - 38;
    }
}

int main()
{
    int sum = 0;
    string line[3];

    while (cin >> line[0] >> line[1] >> line[2])
    {
        // find elements used in each of the 3 rucksacks
        int items[3][53] = {};
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < line[i].size(); j++)
            {
                int prio = get_item_prio(line[i][j]);
                items[i][prio] += 1;
            }
        }
        // find item that is used in all 3 rucksacks
        for (int k = 1; k < 53; k++)
        {
            if (items[0][k] > 0 && items[1][k] > 0 && items[2][k] > 0)
            {
                sum += k;
                break;
            }
        }
    }

    cout << sum << endl;
}
