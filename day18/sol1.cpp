#include <bits/stdc++.h>
using namespace std;
int main()
{
    string line;
    map<string, bool> cube;
    int count = 0;
    while (cin >> line)
    {
        int x = stoi(strtok(&line[0], ","));
        int y = stoi(strtok(NULL, ","));
        int z = stoi(strtok(NULL, ","));
        // cout << "looking at: " << x << "," << y << "," << z << endl;
        count += 6;
        for (int i = x - 1; i <= x + 1; i++)
        {
            for (int j = y - 1; j <= y + 1; j++)
            {
                for (int k = z - 1; k <= z + 1; k++)
                {
                    if ((abs(x - i) + abs(y - j) + abs(z - k)) > 1)
                    {
                        continue;
                    }
                    else
                    {
                        string next = to_string(i) + "," + to_string(j) + "," + to_string(k);
                        count -= (2 * cube.count(next));
                    }
                }
            }
        }
        string state = to_string(x) + "," + to_string(y) + "," + to_string(z);
        cube[state] = true;
    }
    cout << count << endl;
}
