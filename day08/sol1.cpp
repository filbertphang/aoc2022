#include <bits/stdc++.h>
using namespace std;
int main()
{
    char in;
    int map[99][99];
    int visible[99][99] = {};

    // parse map
    for (int i = 0; i < 99; i++)
    {
        for (int j = 0; j < 99; j++)
        {
            cin >> in;
            map[i][j] = (int)in;
        }
    }

    // set all edges to visible
    for (int i = 0; i < 99; i++)
    {
        visible[0][i] = 1;
        visible[98][i] = 1;
        visible[i][0] = 1;
        visible[i][98] = 1;
    }

    // iterate over rows
    for (int row = 1; row < 98; row++)
    {
        // forward direction
        int cur_max = -1;
        for (int col = 0; col < 99; col++)
        {
            if (map[row][col] > cur_max)
            {
                cur_max = map[row][col];
                visible[row][col] = 1;
            }
        }
        // backwards direction
        cur_max = -1;
        for (int col = 98; col >= 0; col--)
        {
            if (map[row][col] > cur_max)
            {
                cur_max = map[row][col];
                visible[row][col] = 1;
            }
        }
    }

    // iterate over cols
    for (int col = 1; col < 98; col++)
    {
        // forward direction
        int cur_max = -1;
        for (int row = 0; row < 99; row++)
        {
            if (map[row][col] > cur_max)
            {
                cur_max = map[row][col];
                visible[row][col] = 1;
            }
        }
        // backwards direction
        cur_max = -1;
        for (int row = 98; row >= 0; row--)
        {
            if (map[row][col] > cur_max)
            {
                cur_max = map[row][col];
                visible[row][col] = 1;
            }
        }
    }

    // sum visible trees
    int sum = 0;
    for (int i = 0; i < 99; i++)
    {
        for (int j = 0; j < 99; j++)
        {
            sum += visible[i][j];
        }
    }

    cout << sum << endl;
}
