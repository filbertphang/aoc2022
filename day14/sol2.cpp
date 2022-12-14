#include <bits/stdc++.h>
using namespace std;

int ymax = 0;
const int LINES = 155;
map<int, map<int, bool>> grid; // x, then y

// since every grain of  sand will either fall to rest (somewhere)
// or cannot be dropped, we only need 2 return values
// returns:
// - false, if this sand cannot be dropped
// - true, if the sand ends in a stable position
bool drop_sand(int start_x, int start_y)
{
    // some obstruction within the same column
    if (grid.find(start_x) != grid.end())
    {
        map<int, bool> *col = &grid[start_x];
        map<int, bool>::iterator obs_it = col->lower_bound(start_y);
        // no obstruction below the sand's current position
        // sand can fall freely to the floor
        if (obs_it == col->end())
        {
            grid[start_x][ymax + 1] = true;
            return true;
        }
        // obstruction is at the sand's current position
        // sand cannot be dropped
        else if (obs_it->first == start_y)
        {
            return false;
        }
        // some obstruction below the sand's current position
        // drop to diagonal left, then diagonal right
        else
        {
            int next_y = obs_it->first;
            // try drop diagonally left first
            bool diag_left = drop_sand(start_x - 1, next_y);
            if (diag_left)
            {
                return diag_left;
            }
            else
            {
                // try dropping diagonally right next
                bool diag_right = drop_sand(start_x + 1, next_y);
                if (diag_right)
                {
                    return diag_right;
                }
                // cannot drop either diagonals
                // set send to rest at current spot
                else
                {
                    grid[start_x][next_y - 1] = true;
                    return true;
                }
            }
        }
    }
    // no obstructions in the same column
    // sand can fall freely to the floor
    else
    {
        grid[start_x][ymax + 1] = true;
        return true;
    }
}

int main()
{
    string line;
    regex num("[0-9]+");
    regex_token_iterator<string::iterator> rend;
    for (int z = 0; z < LINES; z++)
    {
        // parse rock formations
        getline(cin, line);
        regex_token_iterator<string::iterator> matches(line.begin(), line.end(), num);
        int x1, y1;
        int x2 = stoi(*matches++);
        int y2 = stoi(*matches++);
        ymax = max(ymax, y2);
        while (matches != rend)
        {
            x1 = x2;
            y1 = y2;
            x2 = stoi(*matches++);
            y2 = stoi(*matches++);

            // keep track of the largest y-value
            ymax = max(ymax, y2);

            // create rocks between (x1,y1) and (x2,y2)
            if (x1 == x2)
            {
                for (int i = min(y1, y2); i <= max(y1, y2); i++)
                {
                    grid[x1][i] = true;
                }
            }
            else if (y1 == y2)
            {
                for (int i = min(x1, x2); i <= max(x1, x2); i++)
                {
                    grid[i][y1] = true;
                }
            }
        }
    }

    // stop counting when we can no longer drop sand at (500,0)
    int count = 1;
    bool res = drop_sand(500, 0);
    while (res)
    {
        res = drop_sand(500, 0);
        count += 1;
    }
    cout << count - 1 << endl;
}
