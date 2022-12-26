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
    while (num_match != rend)
    {
        steps.push(stoi(*num_match++));
    }
    while (dir_match != rend)
    {
        dir.push(*(dir_match++));
    }
}
