#include <bits/stdc++.h>
using namespace std;

const int TIME = 32;
const int N = 3;

// for each blueprint:
// columns: [ore, clay, obsidian, geode] costs for that robot
// rows: [ore, clay, obsidian] robot schematics
int bp[N + 1][4][3];
int max_ore;
int max_clay;
int max_obs;

// resources: [ore, clay, obsidian, geode]
// robots: [ore, clay, obsidian, geode]
int simulate(int id, int time, int next, int ore, int clay, int obs, int geo, int ore_r, int clay_r, int obs_r, int geo_r)
{

    // decide to build a robot or not
    int robot_built = -1;

    // build ore robot next
    if (next == 0 && ore >= bp[id][0][0])
    {
        robot_built = 0;
        ore -= bp[id][0][0];
    }

    // build clay robot next
    else if (next == 1 && ore >= bp[id][1][0])
    {
        robot_built = 1;
        ore -= bp[id][1][0];
    }

    // build obsidian robot next
    else if (next == 2 && ore >= bp[id][2][0] && clay >= bp[id][2][1])
    {
        robot_built = 2;
        ore -= bp[id][2][0];
        clay -= bp[id][2][1];
    }

    // build geode robot next
    else if (next == 3 && ore >= bp[id][3][0] && obs >= bp[id][3][2])
    {
        robot_built = 3;
        ore -= bp[id][3][0];
        obs -= bp[id][3][2];
    }

    // collect new resources
    ore += ore_r;
    clay += clay_r;
    obs += obs_r;
    geo += geo_r;

    // printf("%d > %d: %d %d %d %d / %d %d %d %d\n", time, next, ore, clay, obs, geo, ore_r, clay_r, obs_r, geo_r);

    // terminate if the time is up
    if (time == TIME)
    {
        return geo;
    }

    // we built a robot, see which robot to build next
    if (robot_built != -1)
    {
        if (robot_built == 0)
        {
            ore_r += 1;
        }
        else if (robot_built == 1)
        {
            clay_r += 1;
        }
        else if (robot_built == 2)
        {
            obs_r += 1;
        }
        else if (robot_built == 3)
        {
            geo_r += 1;
        }

        // check if the current resource values are sufficient
        // to produce robots for all future time stamps
        // if so, we no longer need to produce more of those robots
        bool enough_ore = (ore / max_ore) > (TIME - time);
        bool enough_clay = (clay / max_clay) > (TIME - time);
        bool enough_obs = (obs / max_obs) > (TIME - time);

        // [build ore next, build clay next, build obs next, build geo next]
        int options[4] = {0, 0, 0, 0};

        // also, since we can only produce one robot every turn
        // if the maximum ore cost for any robot is x, we do not need to have
        // more than x ore robots. likewise for the other materials
        // these optimizations reduce the search space sufficiently so we can
        // solve for the correct answer in a reasonable time
        if (ore_r < max_ore && !enough_ore)
        {
            options[0] = simulate(id, time + 1, 0, ore, clay, obs, geo, ore_r, clay_r, obs_r, geo_r);
            // cout << "\n";
        }

        if (clay_r < max_clay && !enough_clay)
        {
            options[1] = simulate(id, time + 1, 1, ore, clay, obs, geo, ore_r, clay_r, obs_r, geo_r);
            // cout << "\n";
        }

        if (clay_r > 0 && obs_r < max_obs && !enough_obs)
        {
            options[2] = simulate(id, time + 1, 2, ore, clay, obs, geo, ore_r, clay_r, obs_r, geo_r);
            // cout << "\n";
        }
        if (obs_r > 0)
        {
            options[3] = simulate(id, time + 1, 3, ore, clay, obs, geo, ore_r, clay_r, obs_r, geo_r);
            // cout << "\n";
        }

        int max_geo = *max_element(begin(options), end(options));
        return max_geo;
    }
    // cannot build a robot, go to next step
    else
    {
        return simulate(id, time + 1, next, ore, clay, obs, geo, ore_r, clay_r, obs_r, geo_r);
    }
}

int main()
{
    // init bp to 0
    for (int i = 1; i < N + 1; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                bp[i][j][k] = 0;
            }
        }
    }
    string line;
    regex num("[0-9]+");

    while (!cin.eof())
    {
        getline(cin, line);
        regex_token_iterator<string::iterator> num_match(line.begin(), line.end(), num);

        int id = stoi(*num_match++);
        // ore robot costs
        bp[id][0][0] = stoi(*num_match++);
        // clay robot costs
        bp[id][1][0] = stoi(*num_match++);
        // obsidian robot costs
        bp[id][2][0] = stoi(*num_match++);
        bp[id][2][1] = stoi(*num_match++);
        // geode robot costs
        bp[id][3][0] = stoi(*num_match++);
        bp[id][3][2] = stoi(*num_match);
    }

    int largest = 1;
    for (int id = 1; id < N + 1; id++)
    {
        // determine maximum resource costs for any robot for that blueprint
        max_ore = max(bp[id][0][0], max(bp[id][1][0], max(bp[id][2][0], bp[id][3][0])));
        max_clay = bp[id][2][1];
        max_obs = bp[id][3][2];

        // simulate blueprint. we can start by building an ore robot or a clay robot
        cout << "simulating blueprint: " << id << endl;
        int start_ore = simulate(id, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0);
        int start_clay = simulate(id, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0);

        // compute product of largest
        largest *= max(start_ore, start_clay);
    }

    cout << largest << endl;
}
