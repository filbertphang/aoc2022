#include <bits/stdc++.h>
using namespace std;

int main()
{
    map<int, map<int, char>> walls; // column, then row
    vector<pair<int, int>> rows;
    vector<pair<int, int>> cols;

    // parse grove map following the rows
    string line;
    int row_n = 0;
    getline(cin, line);
    while (line.size() > 0)
    {
        cout << line << " " << line.size() << endl;
        bool started = false;
        pair<int, int> *cur_row = new pair<int, int>();

        for (int i = 0; i < line.size(); i++)
        {
            // get starting position of row
            if (line[i] == '.' || line[i] == '#')
            {
                if (!started)
                {
                    started = true;
                    cur_row->first = i;
                }

                // store walls position
                if (walls.count(i) == 1)
                {
                    walls[i][row_n] = line[i];
                }
                else
                {
                    map<int, char> *cur_col_walls = new map<int, char>();
                    (*cur_col_walls)[row_n] = line[i];
                    walls[i] = *cur_col_walls;
                }
            }
        }
        cur_row->second = line.size() - 1;

        rows.push_back(*cur_row);
        row_n += 1;
        getline(cin, line);
    }

    // get column data from grove map
    for (pair<int, map<int, char>> col : walls)
    {
        int start = col.second.begin()->first;
        int end = col.second.rbegin()->first;
        pair<int, int> *cur_col = new pair<int, int>();
        cur_col->first = start;
        cur_col->second = end;
        cols.push_back(*cur_col);
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
    int x = rows[0].first;
    int y = 0;
    int d = 0;

    while (!steps.empty())
    {
        // cout << " current position: (" << x << ", " << y << "). \n";
        int step = steps.front();
        steps.pop();

        int new_x = x;
        int new_y = y;

        // move forward x steps
        for (int i = 0; i < step; i++)
        {
            // current direction:
            // 0: right
            // 1: down
            // 2: left
            // 3: up

            // get next position
            if (d == 0)
            {
                new_x += 1;
                if (new_x > rows[y].second)
                {
                    new_x = rows[y].first;
                }
            }
            else if (d == 1)
            {
                new_y += 1;
                if (new_y > cols[x].second)
                {
                    new_y = cols[x].first;
                }
            }
            else if (d == 2)
            {
                new_x -= 1;
                if (new_x < rows[y].first)
                {
                    new_x = rows[y].second;
                }
            }
            else if (d == 3)
            {
                new_y -= 1;
                if (new_y < cols[x].first)
                {
                    new_y = cols[x].second;
                }
            }

            // check if there is a wall in the way
            if (walls[new_x][new_y] == '#')
            {
                // cout << "ran into a wall at: (" << new_x << ", " << new_y << "). \n";
                break;
            }
            else
            {
                x = new_x;
                y = new_y;
            }
        }

        // change direction
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
    int password = (x + 1) * 4 + (y + 1) * 1000 + d;
    cout << "password: " << password << "\n";
}
