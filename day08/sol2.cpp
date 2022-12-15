#include <bits/stdc++.h>
using namespace std;
int main()
{
    // init variables
    const int BOUND = 99;
    char in;
    int map[BOUND][BOUND];
    int scenic[BOUND][BOUND] = {};

    // parse map
    for (int i = 0; i < BOUND; i++)
    {
        for (int j = 0; j < BOUND; j++)
        {
            cin >> in;
            map[i][j] = (int)in - 48;
        }
    }

    // init scenic scores for each tree to 1, except for edges
    for (int i = 1; i < BOUND - 1; i++)
    {
        for (int j = 1; j < BOUND - 1; j++)
        {
            scenic[i][j] = 1;
        }
    }

    /*
        idea: assign each tree a height and a sight value.
        for each direction, we set the first tree to have a sight value of 0.
        we then push that tree's height and sight value to the respective stacks.
        when we go to the next tree, we pop all elements in the stack that have a
        smaller height value than that tree, and add their respective sight values
        to the current sight value of that tree.
        (this makes sense as a higher tree can see as far as all previous trees)
        we then proceed to push to both stacks and multiply the scenic values of that
        tree by the scenic value.
    */
    // iterate over rows
    vector<int> height_stack;
    vector<int> sight_stack;
    for (int row = 1; row < BOUND - 1; row++)
    {
        // from left direction
        height_stack.clear();
        sight_stack.clear();
        int sight = 0;
        for (int col = 0; col < BOUND; col++)
        {
            while (!height_stack.empty() && height_stack.back() < map[row][col])
            {
                sight += sight_stack.back();
                height_stack.pop_back();
                sight_stack.pop_back();
            }
            height_stack.push_back(map[row][col]);
            sight_stack.push_back(sight);
            scenic[row][col] *= sight;
            sight = 1;
        }

        // from right direction
        height_stack.clear();
        sight_stack.clear();
        sight = 0;
        for (int col = 98; col >= 0; col--)
        {
            while (!height_stack.empty() && height_stack.back() < map[row][col])
            {
                sight += sight_stack.back();
                height_stack.pop_back();
                sight_stack.pop_back();
            }
            height_stack.push_back(map[row][col]);
            sight_stack.push_back(sight);
            scenic[row][col] *= sight;
            sight = 1;
        }
    }

    // iterate over cols
    for (int col = 1; col < BOUND - 1; col++)
    {
        // from top direction
        height_stack.clear();
        sight_stack.clear();
        int sight = 0;
        for (int row = 0; row < BOUND; row++)
        {
            while (!height_stack.empty() && height_stack.back() < map[row][col])
            {
                sight += sight_stack.back();
                height_stack.pop_back();
                sight_stack.pop_back();
            }
            height_stack.push_back(map[row][col]);
            sight_stack.push_back(sight);
            scenic[row][col] *= sight;
            sight = 1;
        }

        // from bottom direction
        height_stack.clear();
        sight_stack.clear();
        sight = 0;
        for (int row = 98; row >= 0; row--)
        {
            while (!height_stack.empty() && height_stack.back() < map[row][col])
            {
                sight += sight_stack.back();
                height_stack.pop_back();
                sight_stack.pop_back();
            }
            height_stack.push_back(map[row][col]);
            sight_stack.push_back(sight);
            scenic[row][col] *= sight;
            sight = 1;
        }
    }

    // get maximum scenic score
    int max_scenic = -1;
    for (int i = 0; i < BOUND; i++)
    {
        for (int j = 0; j < BOUND; j++)
        {
            max_scenic = max(max_scenic, scenic[i][j]);
        }
    }

    cout << max_scenic << endl;
}
