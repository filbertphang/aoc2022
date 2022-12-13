#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int M = 93;
const int N = 41;
vector<bool> v;
vector<vector<int>> g;
int grid[N][M];

void edge(int a_i, int a_j, int b_i, int b_j)
{
    int a = (a_i * M) + a_j;
    int b = (b_i * M) + b_j;
    if (grid[b_i][b_j] <= grid[a_i][a_j] + 1)
    {
        g[a].pb(b);
    }
}

int bfs(int u, int end)
{
    queue<int> q;
    queue<int> steps;

    q.push(u);
    steps.push(0);
    v[u] = true;

    while (!q.empty())
    {

        int f = q.front();
        int step = steps.front();
        q.pop();
        steps.pop();

        // cout << f << " ";
        if (f == end)
        {
            return step;
        }

        // Enqueue all adjacent of f and mark them visited
        /*for (auto i = g[f].begin(); i != g[f].end(); i++)
        {
            auto lmfao = g[f];
            auto xd = *i;
            if (!v[*i])
            {
                q.push(*i);
                steps.push(step + 1);
                v[*i] = true;
            }
        }*/
        for (int i : g[f])
        {
            if (!v[i])
            {
                q.push(i);
                steps.push(step + 1);
                v[i] = true;
            }
        }
    }
    return -1;
}

/*
idea: model the grid as a graph
each square is a vertex. we draw an edge between 2 vertices a and b if it is possible
to travel from a to b.

bfs code is from the following website, with some modifications:
https://www.geeksforgeeks.org/bfs-using-stl-competitive-coding/
*/
int main()
{
    // parse grid
    int start;
    int end;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            char c;
            cin >> c;
            if (c == 'S')
            {
                start = (i * M) + j;
                c = 'a';
            }
            if (c == 'E')
            {
                end = (i * M) + j;
                c = 'z';
            }
            grid[i][j] = c - 97;
        }
    }

    // init vertices and edges
    v.assign(N * M, false);
    g.assign(N * M, vector<int>());

    // read edge list from graph
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (i - 1 >= 0)
            {
                edge(i, j, i - 1, j);
            }
            if (i + 1 < N)
            {
                edge(i, j, i + 1, j);
            }
            if (j - 1 >= 0)
            {
                edge(i, j, i, j - 1);
            }
            if (j + 1 < M)
            {
                edge(i, j, i, j + 1);
            }
        }
    }

    // run bfs
    int min_steps = bfs(start, end);
    cout << min_steps << endl;
}
