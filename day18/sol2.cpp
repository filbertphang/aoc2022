#include <bits/stdc++.h>
using namespace std;

// a sufficiently large number
const int LARGE = 9999999;

void update_limit(pair<int, int> *lim, int tar)
{
    if (lim->first > tar)
    {
        lim->first = tar;
    }
    if (lim->second < tar)
    {
        lim->second = tar;
    }
}

int main()
{
    string line;

    // stack to store coordinates
    vector<int> xs;
    vector<int> ys;
    vector<int> zs;

    // store min and max values for x, y, and z axes
    pair<int, int> xlim(LARGE, -1);
    pair<int, int> ylim(LARGE, -1);
    pair<int, int> zlim(LARGE, -1);

    // parse input
    while (cin >> line)
    {
        // get current x,y,z coordinate of droplet
        int x = stoi(strtok(&line[0], ","));
        int y = stoi(strtok(NULL, ","));
        int z = stoi(strtok(NULL, ","));

        // store droplet coordinate in vectors
        xs.push_back(x);
        ys.push_back(y);
        zs.push_back(z);

        // update x/y/z limits accordingly
        update_limit(&xlim, x);
        update_limit(&ylim, y);
        update_limit(&zlim, z);
    }

    // set up flood fill map
    // set boundaries of map to be +-1 of the space occupied by the droplet
    int xlen = xlim.second - xlim.first + 3;
    int ylen = ylim.second - ylim.first + 3;
    int zlen = zlim.second - zlim.first + 3;

    // initialise map to 0 (unvisited)
    int arr[xlen][ylen][zlen];
    for (int i = 0; i < xlen; i++)
    {
        for (int j = 0; j < ylen; j++)
        {
            for (int k = 0; k < zlen; k++)
            {
                arr[i][j][k] = 0;
            }
        }
    }

    // set coordinates of droplets to 2 (rock) and clear stack
    while (!xs.empty())
    {
        int x = xs.back() - xlim.first + 1;
        int y = ys.back() - ylim.first + 1;
        int z = zs.back() - zlim.first + 1;
        arr[x][y][z] = 2;
        xs.pop_back();
        ys.pop_back();
        zs.pop_back();
    }

    // run flood fill
    // use coordinate stacks to store positions of cells to visit
    int count = 0;
    xs.push_back(0);
    ys.push_back(0);
    zs.push_back(0);

    // repeat until there are no cells left to visit
    while (!xs.empty())
    {
        // get current cell
        int x = xs.back();
        int y = ys.back();
        int z = zs.back();
        xs.pop_back();
        ys.pop_back();
        zs.pop_back();
        // do not re-visit previously visited cells
        if (arr[x][y][z] != 0)
        {
            continue;
        }
        arr[x][y][z] = 1;

        // repeat for each adjacent cell
        for (int xn = max(0, x - 1); xn < min(xlen, x + 2); xn++)
        {
            for (int yn = max(0, y - 1); yn < min(ylen, y + 2); yn++)
            {
                for (int zn = max(0, z - 1); zn < min(zlen, z + 2); zn++)
                {
                    // skip tiles that are not directly adjacent
                    int dist = abs(xn - x) + abs(yn - y) + abs(zn - z);
                    if (dist > 1)
                    {
                        continue;
                    }
                    // add unvisited cells to stack
                    if (arr[xn][yn][zn] == 0)
                    {
                        xs.push_back(xn);
                        ys.push_back(yn);
                        zs.push_back(zn);
                    }
                    // skip previously-visited cells
                    else if (arr[xn][yn][zn] == 1)
                    {
                        continue;
                    }
                    // count faces of the droplet that are exposed
                    else if (arr[xn][yn][zn] == 2)
                    {
                        count += 1;
                    }
                }
            }
        }
    }
    cout << count << endl;
}