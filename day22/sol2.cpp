#include <bits/stdc++.h>
using namespace std;

const int SIZE = 50;

struct Face
{
    // <direction, orientation>
    // orientation of the next face is given in terms
    // of # right rotations away from "up"
    pair<int, int> dirs[4];
    char grid[SIZE][SIZE];
    int top;
    int left;
};

void print_grid(char arr[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cout << arr[i][j];
        }
        cout << '\n';
    }
}

void cp_grid(char src[SIZE][SIZE], char tar[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            tar[i][j] = src[i][j];
        }
    }
}

pair<int, int> rotate_coords(pair<int, int> coords, int times)
{
    if (times <= 0)
    {
        return coords;
    }
    pair<int, int> result;
    result.first = coords.second;
    result.second = SIZE - 1 - coords.first;
    return rotate_coords(result, times - 1);
}

// get the current cube face
int get_face(int x, int y)
{
    if (x >= 0 && x < SIZE)
    {
        return 2;
    }
    else if (x >= SIZE && x < 2 * SIZE)
    {
        return 3;
    }
    else if (x >= 2 * SIZE && x < 3 * SIZE)
    {
        if (y >= 0 && y < SIZE)
        {
            return 1;
        }
        else if (y >= SIZE && y < 2 * SIZE)
        {
            return 4;
        }
        else if (y >= 2 * SIZE && y < 3 * SIZE)
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
        faces[1].dirs[0] = pair<int, int>(2, 0);
        faces[1].dirs[1] = pair<int, int>(3, 0);
        faces[1].dirs[2] = pair<int, int>(4, 2);
        faces[1].dirs[3] = pair<int, int>(6, 3);
        faces[1].top = 0;
        faces[1].left = SIZE;

        // face 2
        faces[2].dirs[0] = pair<int, int>(5, 2);
        faces[2].dirs[1] = pair<int, int>(3, 3);
        faces[2].dirs[2] = pair<int, int>(1, 0);
        faces[2].dirs[3] = pair<int, int>(6, 0);
        faces[2].top = 0;
        faces[2].left = 2 * SIZE;

        // face 3
        faces[3].dirs[0] = pair<int, int>(2, 1);
        faces[3].dirs[1] = pair<int, int>(5, 0);
        faces[3].dirs[2] = pair<int, int>(4, 1);
        faces[3].dirs[3] = pair<int, int>(1, 0);
        faces[3].top = SIZE;
        faces[3].left = SIZE;

        // face 4
        faces[4].dirs[0] = pair<int, int>(5, 0);
        faces[4].dirs[1] = pair<int, int>(6, 0);
        faces[4].dirs[2] = pair<int, int>(1, 2);
        faces[4].dirs[3] = pair<int, int>(3, 3);
        faces[4].top = 2 * SIZE;
        faces[4].left = 0;

        // face 5
        faces[5].dirs[0] = pair<int, int>(2, 2);
        faces[5].dirs[1] = pair<int, int>(6, 3);
        faces[5].dirs[2] = pair<int, int>(4, 0);
        faces[5].dirs[3] = pair<int, int>(3, 0);
        faces[5].top = 2 * SIZE;
        faces[5].left = SIZE;

        // face 6
        faces[6].dirs[0] = pair<int, int>(5, 1);
        faces[6].dirs[1] = pair<int, int>(2, 0);
        faces[6].dirs[2] = pair<int, int>(1, 1);
        faces[6].dirs[3] = pair<int, int>(4, 0);
        faces[6].top = 3 * SIZE;
        faces[6].left = 0;
    }

    // parse input
    string line;
    int cur_face;
    for (int row = 0; row < 4 * SIZE; row++)
    {
        getline(cin, line);
        if (row >= 0 && row < SIZE)
        {
            cur_face = 1;
            for (int col = SIZE; col < 3 * SIZE; col++)
            {
                if (col == 2 * SIZE)
                {
                    cur_face += 1;
                }
                faces[cur_face].grid[row % SIZE][col % SIZE] = line[col];
            }
        }
        else if (row >= SIZE && row < 2 * SIZE)
        {
            cur_face = 3;
            for (int col = SIZE; col < 2 * SIZE; col++)
            {
                faces[cur_face].grid[row % SIZE][col % SIZE] = line[col];
            }
        }
        else if (row >= 2 * SIZE && row < 3 * SIZE)
        {
            cur_face = 4;
            for (int col = 0; col < 2 * SIZE; col++)
            {
                if (col == SIZE)
                {
                    cur_face += 1;
                }
                faces[cur_face].grid[row % SIZE][col % SIZE] = line[col];
            }
        }
        else if (row >= 3 * SIZE && row < 4 * SIZE)
        {
            cur_face = 6;
            for (int col = 0; col < SIZE; col++)
            {
                faces[cur_face].grid[row % SIZE][col % SIZE] = line[col];
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
    int d = 0;
    char grid[SIZE][SIZE];
    cp_grid(faces[1].grid, grid);
    while (!steps.empty())
    {
        int step = steps.front();
        steps.pop();
        // cout << "\nface: " << face << " (x,y): " << x << ", " << y << " dir: " << d << " steps: " << step << "\n";

        int new_x = x;
        int new_y = y;
        int new_face = face;
        int new_orient = 0;
        int new_d = d;
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
            }
            else if (d == 1)
            {
                new_y = y + 1;
            }
            else if (d == 2)
            {
                new_x = x - 1;
            }
            else if (d == 3)
            {
                new_y = y - 1;
            }

            if (new_x >= SIZE || new_x < 0 || new_y >= SIZE || new_y < 0)
            {
                // cout << "  overshot at (x,y): " << new_x << ", " << new_y << " dir: " << new_d << "\n";
                new_x = (new_x + SIZE) % SIZE;
                new_y = (new_y + SIZE) % SIZE;
                new_orient = faces[face].dirs[d].second;
                pair<int, int> next = rotate_coords(pair<int, int>(new_x, new_y), new_orient);
                new_x = next.first;
                new_y = next.second;
                new_d = (d + (4 - new_orient)) % 4;
                new_face = faces[face].dirs[d].first;
                // cout << "  changing face to " << new_face << ", (x,y): " << new_x << ", " << new_y << " dir: " << new_d << "\n";
            }

            if (faces[new_face].grid[new_y][new_x] == '#')
            {
                // cout << "found wall at face: " << new_face << " (x,y): " << x << ", " << y << "\n";
                break;
            }
            else
            {
                x = new_x;
                y = new_y;
                d = new_d;
                face = new_face;
            }
        }

        if (!dir.empty())
        {
            string next_d = dir.front();
            dir.pop();

            if (next_d == "L")
            {
                d -= 1;
                if (d < 0)
                {
                    d = 3;
                }
            }
            else
            {
                d = (d + 1) % 4;
            }
        }
    }

    cout << "final x: " << x << "\n";
    cout << "final y: " << y << "\n";
    cout << "final d: " << d << "\n";
    cout << "final face: " << face << "\n\n";
    int password = 1000 * ((y + faces[face].top) + 1) + 4 * ((x + faces[face].left) + 1) + d;
    cout << "password: " << password << "\n\n";
}