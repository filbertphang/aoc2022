#include <bits/stdc++.h>
using namespace std;

const int WIDTH = 7;

struct rock
{
    int width;
    int height;
};

// csearch: convenient search
bool csearch(set<int, greater<int>> v, int val)
{
    return v.count(val) == 1;
}

// cmax: convenient max
// only need one parameter
int cmax(set<int, greater<int>> v)
{
    return *(v.begin());
}

// clb: convenient lower bound
// its just shorter
int clb(set<int, greater<int>> v, int val)
{
    return *(v.lower_bound(val));
}

void print_hts(set<int, greater<int>> heights[WIDTH])
{
    for (int z = 0; z < WIDTH; z++)
    {
        cout << cmax(heights[z]) << " ";
    }
    // cout << "col: " << cur_col << " row: " << cur_row << " dir: " << dir << " p: " << p << endl;
    cout << "\n";
}

int main()
{
    // store y-coordinates of positions in each column
    // that are occupied by a rock (or floor)
    set<int, greater<int>> heights[WIDTH];
    for (int h = 0; h < WIDTH; h++)
    {
        heights[h].insert(0);
    }

    rock types[5] = {
        {4, 1},
        {3, 3},
        {3, 3},
        {1, 4},
        {2, 2}};

    int p = 0;
    string pattern;
    cin >> pattern;

    // rock positions are given by their leftmost and bottommost coordinate
    // i.e. for the following rock types, let o denote the rock's position
    //  0     1    2   3    4
    // o###  .#.  ..#  #   ##
    //       o##  ..#  #   o#
    //       .#.  o##  #
    //                 o
    //
    int cur_type = 0; // type of rock
    rock *cur_rock = &types[cur_type];
    int cur_col = 2;
    int cur_row = 4;
    int max_height = 0;
    int rock_count = 0;
    while (rock_count < 2022)
    {
        // get the current wind direction
        char dir = pattern[p];

        // print shapes
        // print_hts(heights);

        // handle horizontal movement
        bool has_obstruction;
        if (dir == '<')
        {
            bool left_wall = cur_col == 0;

            // check for obstructions in moving left
            if (cur_type == 1)
            {
                has_obstruction = left_wall ||
                                  csearch(heights[cur_col], cur_row + 1) ||
                                  csearch(heights[cur_col], cur_row - 1) ||
                                  csearch(heights[cur_col - 1], cur_row);
            }
            else if (cur_type == 2)
            {
                has_obstruction = left_wall ||
                                  csearch(heights[cur_col - 1], cur_row) ||
                                  csearch(heights[cur_col + 1], cur_row + 1) ||
                                  csearch(heights[cur_col + 1], cur_row + 2);
            }
            else
            {
                has_obstruction = left_wall;
                for (int i = 0; i < types[cur_type].height; i++)
                {
                    has_obstruction = has_obstruction || csearch(heights[cur_col - 1], cur_row + i);
                }
            }

            if (!has_obstruction)
            {
                // cout << "moving left" << endl;
                cur_col -= 1;
            }
        }
        else if (dir == '>')
        {
            int right_col = cur_col + types[cur_type].width - 1;
            bool right_wall = right_col >= WIDTH - 1;

            // check for obstructions in moving right
            if (cur_type == 1)
            {
                has_obstruction = right_wall ||
                                  csearch(heights[right_col], cur_row + 1) ||
                                  csearch(heights[right_col], cur_row - 1) ||
                                  csearch(heights[right_col + 1], cur_row);
            }
            else
            {
                has_obstruction = right_wall;
                for (int i = 0; i < types[cur_type].height; i++)
                {
                    has_obstruction = has_obstruction || csearch(heights[right_col + 1], cur_row + i);
                }
            }

            // move right if there are no obstructions
            if (!has_obstruction)
            {
                // cout << "moving right" << endl;
                cur_col += 1;
            }
        }

        // handle vertical movement
        bool landed = false;
        // cout << "current rock type: " << cur_type << "\n";
        if (cur_type == 1)
        {
            // check if we can fall
            int h1 = clb(heights[cur_col], cur_row);
            int h2 = clb(heights[cur_col + 1], cur_row);
            int h3 = clb(heights[cur_col + 2], cur_row);

            bool can_fall = (h1 < cur_row - 1) && (h2 < cur_row - 2) && (h3 < cur_row - 1);
            // if we can fall, let the rock fall
            if (can_fall)
            {
                // cout << "rock can fall!\n";
                cur_row -= 1;
            }
            // else, mark the spaces occupied by this rock
            else
            {
                // cout << "rock is landing\n";
                heights[cur_col].insert(cur_row);
                heights[cur_col + 1].insert(cur_row - 1);
                heights[cur_col + 1].insert(cur_row);
                heights[cur_col + 1].insert(cur_row + 1);
                heights[cur_col + 2].insert(cur_row);
                max_height = max(max_height, cur_row + 1);
                landed = true;
            }
        }
        else
        {
            // check if we can fall
            bool can_fall = true;
            for (int h = cur_col; h < cur_col + types[cur_type].width; h++)
            {
                can_fall = can_fall && (clb(heights[h], cur_row) < cur_row - 1);
                if (!can_fall)
                {
                    break;
                }
            }

            // if we can fall, let the rock fall
            if (can_fall)
            {
                // cout << "rock can fall!\n";
                cur_row -= 1;
            }
            // else, mark the spaces occupied by this rock
            else
            {
                // cout << "rock is landing\n";
                // handle rock type 2 differently
                if (cur_type == 2)
                {
                    heights[cur_col].insert(cur_row);
                    heights[cur_col + 1].insert(cur_row);
                    heights[cur_col + 2].insert(cur_row);
                    heights[cur_col + 2].insert(cur_row + 1);
                    heights[cur_col + 2].insert(cur_row + 2);
                    max_height = max(max_height, cur_row + 2);
                }
                else
                {
                    for (int c = cur_col; c < cur_col + types[cur_type].width; c++)
                    {
                        for (int r = cur_row; r < cur_row + types[cur_type].height; r++)
                        {
                            heights[c].insert(r);
                        }
                    }
                    max_height = max(max_height, cur_row + types[cur_type].height - 1);
                }
                landed = true;
            }
        }

        // if the current rock landed, create a new rock
        if (landed)
        {
            // print_hts(heights);
            cur_type = (cur_type + 1) % 5;
            cur_rock = &types[cur_type];
            cur_col = 2;
            cur_row = max_height + 4;
            if (cur_type == 1)
            {
                cur_row += 1;
            }
            rock_count += 1;
        }

        // get the next wind direction
        p = (p + 1) % pattern.size();
    }

    cout << max_height << endl;
}