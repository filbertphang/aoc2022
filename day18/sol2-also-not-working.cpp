#include <bits/stdc++.h>
using namespace std;

map<string, bool> cube;

vector<string> *get_adjacent(int x, int y, int z)
{
    vector<string> *next = new vector<string>();
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
                else if (i == x && j == y && k == z)
                {
                    continue;
                }
                else
                {
                    string state = to_string(i) + "," + to_string(j) + "," + to_string(k);
                    next->push_back(state);
                }
            }
        }
    }
    return next;
}

void remove_tunnels(string line)
{
    string state(line);
    int x = stoi(strtok(&line[0], ","));
    int y = stoi(strtok(NULL, ","));
    int z = stoi(strtok(NULL, ","));
    vector<string> adj = *get_adjacent(x, y, z);
    bool has_void = false;

    for (string s : adj)
    {
        if (cube.count(s) == 0)
        {
            has_void = true;
            break;
        }
    }

    if (has_void)
    {
        // set this tile to void also
        cube.erase(state);

        // recursively remove void tiles from neighbours
        for (string ss : adj)
        {
            if (cube.count(ss) == 1 && !cube[ss])
            {
                remove_tunnels(ss);
            }
        }
    }
}

int main()
{
    string line;
    int count = 0;
    vector<string> blanks;
    while (cin >> line)
    {
        int x = stoi(strtok(&line[0], ","));
        int y = stoi(strtok(NULL, ","));
        int z = stoi(strtok(NULL, ","));
        // cout << "looking at: " << x << "," << y << "," << z << endl;
        count += 6;
        vector<string> adj = *get_adjacent(x, y, z);
        for (string next : adj)
        {
            if (cube.count(next))
            {
                if (cube[next])
                {
                    count -= 2;
                }
            }
            else
            {
                cube[next] = false;
                blanks.push_back(next);
            }
        }
        string state = to_string(x) + "," + to_string(y) + "," + to_string(z);
        cube[state] = true;
    }

    for (string s : blanks)
    {
        if (cube.count(s) == 0 || cube[s])
        {
            continue;
        }
        // DFS to remove all tunnels involving this space
        remove_tunnels(s);
    }

    int empty_space = 0;
    for (string s : blanks)
    {
        if (cube.count(s) == 0 || cube[s])
        {
            continue;
        }
        cout << "looking at: " << s << endl;
        int x = stoi(strtok(&s[0], ","));
        int y = stoi(strtok(NULL, ","));
        int z = stoi(strtok(NULL, ","));

        int diff = 6;
        vector<string> adj = *get_adjacent(x, y, z);
        for (string next : adj)
        {
            if (cube.count(next))
            {
                if (!cube[next])
                {
                    diff -= 1;
                }
            }
        }
        cout << "diff: " << diff << "\n";
        empty_space += diff;
        cube[s] = true;
    }
    cout << count << " " << empty_space << "\n";
    cout << (count - empty_space) << endl;
}
