#include <bits/stdc++.h>
using namespace std;

// simulate head movement
void move_head(char dir, int *head_x, int *head_y)
{
    if (dir == 'U')
    {
        *head_y += 1;
    }
    else if (dir == 'D')
    {
        *head_y -= 1;
    }
    else if (dir == 'R')
    {
        *head_x += 1;
    }
    else if (dir == 'L')
    {
        *head_x -= 1;
    }
}

// simulate tail movement
void move_tail(int head_x, int head_y, int *tail_x, int *tail_y)
{
    // observe that as long as the head is 2 steps away from the tail
    // in any direction, the tail will always follow the head
    // hence, we only have 2 cases: 2 steps away in the x and y directions
    int x_diff = head_x - *tail_x;
    int y_diff = head_y - *tail_y;
    if (x_diff == 2 || x_diff == -2)
    {
        *tail_x += (x_diff / 2);
        *tail_y = head_y;
    }
    else if (y_diff == 2 || y_diff == -2)
    {
        *tail_y += (y_diff / 2);
        *tail_x = head_x;
    }
}

int main()
{
    /*
    idea: simulate head and tail movement, then store all tail positions in an unordered set
    the size of the unordered set is the # of unique positions visited by the tail
    */
    char dir;
    int steps;
    int head_x = 0, head_y = 0;
    int tail_x = 0, tail_y = 0;
    unordered_set<string> visited;
    while (cin >> dir >> steps)
    {
        for (int i = 0; i < steps; i++)
        {
            move_head(dir, &head_x, &head_y);
            move_tail(head_x, head_y, &tail_x, &tail_y);
            string hash = to_string(tail_x) + "," + to_string(tail_y);
            visited.insert(hash);
        }
    }
    cout << visited.size() << endl;
}
