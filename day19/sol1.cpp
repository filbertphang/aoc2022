#include <bits/stdc++.h>
using namespace std;

const int TIME = 24;
const int N = 30;

// for each blueprint:
// columns: [ore, clay, obsidian, geode] costs for that robot
// rows: [ore, clay, obsidian geode] robot schematics
int bp[N + 1][4][4];

// resources: [ore, clay, obsidian, geode]
// robots: [ore, clay, obsidian, geode]
int simulate(int id, int time, int next, int ore, int clay, int obs, int geo, int ore_r, int clay_r, int obs_r, int geo_r)
{
    // collect new resources
    ore += ore_r;
    clay += clay_r;
    obs += obs_r;
    geo += geo_r;

    // terminate if the time is up
    if (time == TIME)
    {
        return geo;
    }

    bool robot_built = false;

    // build ore robot next
    if (next == 0 && ore >= bp[id][0][0])
    {
        robot_built = true;
        ore -= bp[id][0][0];
        ore_r += 1;
    }

    // build clay robot next
    else if (next == 1 && ore >= bp[id][1][0])
    {
        robot_built = true;
        ore -= bp[id][1][0];
        clay_r += 1;
    }

    // build obsidian robot next
    else if (next == 2 && ore >= bp[id][2][0] && clay >= bp[id][2][1])
    {
        robot_built = true;
        ore -= bp[id][2][0];
        clay -= bp[id][2][1];
        obs_r += 1;
    }

    // build geode robot next
    else if (next == 3 && ore >= bp[id][3][0] && obs >= bp[id][3][2])
    {
        robot_built = true;
        ore -= bp[id][3][0];
        obs -= bp[id][3][2];
        geo_r += 1;
    }

    // we built a robot, see which robot to build next
    if (robot_built)
    {
        printf("%d: %d %d %d %d / %d %d %d %d\n", time, ore, clay, obs, geo, ore_r, clay_r, obs_r, geo_r);
        // [build ore next, build clay next, build obs next, build geo next]
        int options[4] = {0, 0, 0, 0};
        options[0] = simulate(id, time + 1, 0, ore, clay, obs, geo, ore_r, clay_r, obs_r, geo_r);
        options[1] = simulate(id, time + 1, 1, ore, clay, obs, geo, ore_r, clay_r, obs_r, geo_r);

        if (clay_r > 0)
        {
            options[2] = simulate(id, time + 1, 2, ore, clay, obs, geo, ore_r, clay_r, obs_r, geo_r);
        }
        if (obs_r > 0)
        {
            options[3] = simulate(id, time + 1, 3, ore, clay, obs, geo, ore_r, clay_r, obs_r, geo_r);
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
            for (int k = 0; k < 4; k++)
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

    int geo[N + 1] = {0};
    for (int id = 1; id < N + 1; id++)
    {
        cout << "simulating blueprint: " << id << endl;
        int start_ore = simulate(id, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0);
        ;
        int start_clay = simulate(id, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0);
        geo[id] = max(start_ore, start_clay);
    }

    // int max_geodes = *max_element(begin(geo), end(geo));
    // cout << max_geodes << endl;
    for (int idd = 1; idd < N + 1; idd++)
    {
        cout << idd << ": " << geo[idd] << "\n";
    }
}
