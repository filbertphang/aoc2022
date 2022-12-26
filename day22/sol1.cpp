#include <bits/stdc++.h>
using namespace std;

struct row
{
    int start;
    int end;
    vector<int> walls;
};

int main()
{
    vector<row> rows;

    // parse grove map
    string line;
    getline(cin, line);
    while (!cin.eof())
    {
        bool started = false;
        row *cur_row = new row();
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == '.' || line[i] == '#')
            {
                // note down the starting position of that row
                if (!started)
                {
                    started = true;
                    cur_row->start = i;
                }
            }
            if (line[i] == '#')
            {
                // add wall to walls list
                cur_row->walls.push_back(i);
            }
        }
        cur_row->end = line.size() - 1;

        rows.push_back(*cur_row);
        getline(cin, line);
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
