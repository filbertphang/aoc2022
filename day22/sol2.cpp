#include <bits/stdc++.h>
using namespace std;

struct Face
{
    // <direction, orientation>
    // orientation of the next face is given in terms
    // of # right rotations away from "up"
    pair<int, int> left;
    pair<int, int> right;
    pair<int, int> up;
    pair<int, int> down;
    char grid[50][50];
};

void cp_grid(char src[50][50], char tar[50][50])
{
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            tar[i][j] = src[i][j];
        }
    }
}

void rotate_grid(char grid[50][50], int times)
{
    char orig[50][50];
    cp_grid(grid, orig);
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            grid[j][49 - i] = orig[i][j];
        }
    }
    times -= 1;
    if (times > 0)
    {
        rotate_grid(grid, times);
    }
}

// get the current cube face
int get_face(int x, int y)
{
    if (x >= 0 && x < 50)
    {
        return 2;
    }
    else if (x >= 50 && x < 100)
    {
        return 3;
    }
    else if (x >= 100 && x < 150)
    {
        if (y >= 0 && y < 50)
        {
            return 1;
        }
        else if (y >= 50 && y < 100)
        {
            return 4;
        }
        else if (y >= 100 && y < 150)
        {
            return 5;
        }
    }
    else
    {
        return 6;
    }
}

int main()
{
    // initialise faces
    Face faces[7];
    for (int i = 1; i < 7; i++)
    {
        faces[i] = *(new Face());
    }

    // hard-code directions (sadly)
    {
        // face 1
        faces[1].left = pair<int, int>(4, 2);
        faces[1].right = pair<int, int>(2, 0);
        faces[1].up = pair<int, int>(6, 3);
        faces[1].down = pair<int, int>(3, 0);

        // face 2
        faces[2].left = pair<int, int>(1, 0);
        faces[2].right = pair<int, int>(5, 2);
        faces[2].up = pair<int, int>(6, 0);
        faces[2].down = pair<int, int>(3, 3);

        // face 3
        faces[3].left = pair<int, int>(4, 1);
        faces[3].right = pair<int, int>(2, 1);
        faces[3].up = pair<int, int>(1, 0);
        faces[3].down = pair<int, int>(5, 0);

        // face 4
        faces[4].left = pair<int, int>(1, 2);
        faces[4].right = pair<int, int>(5, 0);
        faces[4].up = pair<int, int>(3, 3);
        faces[4].down = pair<int, int>(6, 0);

        // face 5
        faces[5].left = pair<int, int>(4, 0);
        faces[5].right = pair<int, int>(2, 2);
        faces[5].up = pair<int, int>(3, 0);
        faces[5].down = pair<int, int>(6, 1);

        // face 6
        faces[6].left = pair<int, int>(1, 1);
        faces[6].right = pair<int, int>(5, 1);
        faces[6].up = pair<int, int>(4, 0);
        faces[6].down = pair<int, int>(2, 0);
    }

    // parse input
    string line;
    int cur_face;
    for (int row = 0; row < 200; row++)
    {
        getline(cin, line);
        if (row >= 0 && row < 50)
        {
            cur_face = 1;
            for (int col = 50; col < 150; col++)
            {
                if (col == 100)
                {
                    cur_face += 1;
                }
                faces[cur_face].grid[row % 50][col % 50] = line[col];
            }
        }
        else if (row >= 50 && row < 100)
        {
            cur_face = 3;
            for (int col = 50; col < 100; col++)
            {
                faces[cur_face].grid[row % 50][col % 50] = line[col];
            }
        }
        else if (row >= 100 && row < 150)
        {
            cur_face = 4;
            for (int col = 0; col < 100; col++)
            {
                if (col == 50)
                {
                    cur_face += 1;
                }
                faces[cur_face].grid[row % 50][col % 50] = line[col];
            }
        }
        else if (row >= 150 && row < 200)
        {
            cur_face = 6;
            for (int col = 0; col < 50; col++)
            {
                faces[cur_face].grid[row % 50][col % 50] = line[col];
            }
        }
    }

    // parse directions from monkeys
    regex num_pattern("[0-9]+");
    regex dir_pattern("[LR]");
    regex_token_iterator<string::iterator> rend;
    queue<int> steps;
    queue<string> dir;

    cin >> line;
    regex_token_iterator<string::iterator> num_match(line.begin(), line.end(), num_pattern);
    regex_token_iterator<string::iterator> dir_match(line.begin(), line.end(), dir_pattern);
    while (dir_match != rend)
    {
        string tmp = *(dir_match++);
        dir.push(tmp);
    }
    while (num_match != rend)
    {
        string tmp = *(num_match++);
        steps.push(stoi(tmp));
    }

    // traverse the grove!
    int x = 0;
    int y = 0;
    int face = 1;
    int orient = 0;
    int d = 0;
    char grid[50][50];
    cp_grid(faces[1].grid, grid);
    while (!steps.empty())
    {
        break;
        int step = steps.front();
        steps.pop();

        int new_x = x;
        int new_y = y;
        pair<int, int> new_face;
        char next_grid[50][50];
        // current direction:
        // 0: right
        // 1: down
        // 2: left
        // 3: up
        for (int i = 0; i < step; i++)
        {
            if (d == 0)
            {
                new_x = x + 1;
                new_face = faces[face].right;
            }
            else if (d == 1)
            {
                new_y = y + 1;
                new_face = faces[face].down;
            }
            else if (d == 2)
            {
                new_x = x - 1;
                new_face = faces[face].left;
            }
            else if (d == 3)
            {
                new_y = y - 1;
                new_face = faces[face].up;
            }

            if (x >= 50 || x < 0 || y >= 50 || y < 0)
            {
                cp_grid(faces[new_face.first].grid, next_grid);
            }
        }
    }
}