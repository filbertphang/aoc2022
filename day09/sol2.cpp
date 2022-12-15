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
    // we now have a 3rd case where the head is 2 steps diagonally away from the tail
    int x_diff = head_x - *tail_x;
    int y_diff = head_y - *tail_y;
    if (abs(x_diff) == 2 && abs(y_diff) == 2)
    {
        *tail_x += (x_diff / 2);
        *tail_y += (y_diff / 2);
    }
    else if (abs(x_diff) == 2)
    {
        *tail_x += (x_diff / 2);
        *tail_y = head_y;
    }
    else if (abs(y_diff) == 2)
    {
        *tail_y += (y_diff / 2);
        *tail_x = head_x;
    }
}

int main()
{
    /*
    idea: simulate a movement of 10 ropes as having 1 head and 9 tails
    use the previous tail as the head of the current tail
    the rest of the process is similar as part 1.
    */
    char dir;
    int steps;
    int x_pos[10] = {};
    int y_pos[10] = {};
    unordered_set<string> visited;
    while (cin >> dir >> steps)
    {
        for (int i = 0; i < steps; i++)
        {
            move_head(dir, &x_pos[0], &y_pos[0]);
            for (int tail = 1; tail < 10; tail++)
            {
                move_tail(x_pos[tail - 1], y_pos[tail - 1], &x_pos[tail], &y_pos[tail]);
            }

            string hash = to_string(x_pos[9]) + "," + to_string(y_pos[9]);
            visited.insert(hash);
        }
    }
    cout << visited.size() << endl;
}
