#include <bits/stdc++.h>
using namespace std;

struct Face
{
    pair<int, int> left;
    pair<int, int> right;
    pair<int, int> up;
    pair<int, int> down;
    char grid[50][50];
};

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
    Face faces[7];
    for (int i = 1; i < 7; i++)
    {
        faces[i] = *(new Face());
    }

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
    for (int i = 0; i < 50; i++)
    {

        for (int j = 0; j < 50; j++)
        {
            cout << faces[6].grid[i][j];
        }
        cout << "\n";
    }
}