#include <bits/stdc++.h>
using namespace std;

// globals
const int WIDTH = 7;
const long DURATION = 1000000000000;
set<int, greater<int>> heights[WIDTH];

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

// debug function to print heights
void print_hts(set<int, greater<int>> heights[WIDTH])
{
    for (int z = 0; z < WIDTH; z++)
    {
        cout << cmax(heights[z]) << " ";
    }
    // cout << "col: " << cur_col << " row: " << cur_row << " dir: " << dir << " p: " << p << endl;
    cout << "\n";
}

// gets the board state after a rock has landed
// state includes:
// - rock type that just landed
// - current wind state (i.e. position in the input pattern)
// - board state, which is the height delta between the max height of all columns
//                and the height of each column
//
// the assumption here is that this state is sufficient to detect cycles,
// which it thankfully is! although it can be proven that there are scenarios
// where such an encoding is still insufficient.
string get_state(int rock_count, int min_height, int wind_state)
{
    string state = to_string(rock_count % 5) + "," + to_string(wind_state) + ":";
    for (int i = 0; i < WIDTH; i++)
    {
        int height_diff = *(heights[i].begin()) - min_height;
        state += to_string(height_diff) + ",";
    }
    return state;
}

int main()
{
    // store y-coordinates of positions in each column
    // that are occupied by a rock (or floor)
    for (int h = 0; h < WIDTH; h++)
    {
        heights[h].insert(0);
    }

    // init wind pattern and rock types
    int p = 0;
    string pattern;
    cin >> pattern;
    rock types[5] = {
        {4, 1},
        {3, 3},
        {3, 3},
        {1, 4},
        {2, 2}};

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
    long rock_count = 0;

    // init variables used for cycle detection
    map<string, pair<long, int>> states;
    bool cycle_found = false;
    long cycle_offset = 0;
    long next_cycle;
    int next_cycle_height;
    string next_cycle_state;

    // here we go
    while (rock_count < DURATION)
    {
        // get the current wind direction
        char dir = pattern[p];

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
            // minor optimization: we only need to keep information about the rock structure
            // for rows above the height of the column with the smallest total height
            int min_col = 0;
            int min_height = *(heights[0].rbegin());
            for (int i = 1; i < WIDTH; i++)
            {
                int cur_height = *(heights[i].rbegin());
                if (cur_height < min_height)
                {
                    min_height = cur_height;
                    min_col = i;
                }
            }
            for (int j = 0; j < WIDTH; j++)
            {
                if (j != min_col)
                {
                    set<int, greater<int>>::iterator it = heights[j].upper_bound(min_height);
                    heights[j].erase(it, heights[j].end());
                }
            }

            // cycle detection
            if (!cycle_found)
            {
                // get the current state
                string state = get_state(rock_count, max_height, p);

                // check if this state has been visited before
                // if it has, then we have a cycle
                if (states.count(state) == 1)
                {
                    cout << "cycle found!\n";
                    cycle_found = true;

                    // get cycle properties
                    int start = states[state].first;
                    int cycle_len = rock_count - start;
                    int cycle_ht = max_height - states[state].second;

                    // compute how many cycles we can advance the simulation by
                    // compute the increase in height by advancing the simulation
                    long n_cycles = (DURATION - 1 - rock_count) / cycle_len;
                    cycle_offset = n_cycles * cycle_ht;
                    cout << "cycle starts at: " << start << " with length: " << cycle_len << " and height: " << cycle_ht << endl;

                    // debug: predict the next cycle
                    next_cycle = rock_count + cycle_len;
                    next_cycle_height = max_height + cycle_ht;
                    next_cycle_state = state;
                    cout << "next cycle predicted at: " << next_cycle << " with height: " << next_cycle_height << endl;

                    // advance simulation by that many cycles
                    rock_count += (cycle_len * n_cycles);
                }
                // if we haven't visited the state before,
                // mark it as visited by storing some state data
                // (current # rocks and current maximum height)
                else
                {
                    pair<int, long> *state_data = new pair<int, long>(rock_count, max_height);
                    states[state] = *state_data;
                }
            }

            // create a new rock
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
    // increase current max height by the amount we computed earlier
    // from advancing the simulation
    cycle_offset += max_height;
    cout << cycle_offset << "\n";
}
