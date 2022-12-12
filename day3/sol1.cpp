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
    string line;

    while (cin >> line)
    {
        int items[53] = {};
        int len = line.size() / 2;
        for (int i = 0; i < len; i++)
        {
            int prio = get_item_prio(line[i]);
            items[prio] += 1;
        }
        for (int j = len; j < 2 * len; j++)
        {
            int prio2 = get_item_prio(line[j]);
            if (items[prio2] > 0)
            {
                cout << line[j] << ": " << prio2 << endl;
                sum += prio2;
                break;
            }
        }
    }
    cout << sum << endl;
}
