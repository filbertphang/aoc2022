#include <bits/stdc++.h>
using namespace std;

struct valve
{
    int rate;
    vector<string> tunnels;
};

int find_max_pressure(int time, int pos, string opened, int dist[60][60]);

// it's okay to use global variables for competitive programming, right?
// ... right?
int n_valves;
int n_useful;
const int STEPS = 30;
map<string, int> memo[STEPS];
map<string, int> valve_ids;
vector<valve> valves;
vector<int> useful_valve_ids;
int dist[60][60] = {0}; // hard-coded to be 60x60
string all_opened;

int main()
{
    string line;

    // regex stuff
    regex num("[0-9]+");
    regex name("[A-Z]{2}");
    regex_token_iterator<string::iterator> rend;

    // parse input
    int valve_id = 0;
    while (!cin.eof())
    {
        getline(cin, line);
        valve *cur_valve = new valve();

        // parse valve rate
        regex_token_iterator<string::iterator> num_match(line.begin(), line.end(), num);
        cur_valve->rate = stoi(*num_match);

        // parse valve name
        regex_token_iterator<string::iterator> name_match(line.begin(), line.end(), name);
        string valve_name = *name_match++;

        // parse tunnels to other vaults
        vector<string> *tunnels = new vector<string>();
        while (name_match != rend)
        {
            tunnels->push_back(*name_match++);
        }
        cur_valve->tunnels = *tunnels;

        // store the current valve
        valve_ids[valve_name] = valve_id;
        valves.push_back(*cur_valve);

        // call the current valve "useful" if it has a positive rate
        if (cur_valve->rate > 0)
        {
            useful_valve_ids.push_back(valve_id);
        }

        valve_id += 1;
    }

    // set constants
    n_valves = valve_id;
    n_useful = useful_valve_ids.size();

    // init distance array with a large value,
    // and set initial distances between adjacent valves to 1
    for (int row = 0; row < n_valves; row++)
    {
        for (int col = 0; col < n_valves; col++)
        {
            dist[row][col] = n_valves + 100;
        }
        for (string vname : valves[row].tunnels)
        {
            int vid = valve_ids[vname];
            dist[row][vid] = 1;
            dist[vid][row] = 1;
        }
    }

    // use Floyd-Warshall to find all-pairs shortest path between all valves
    for (int k = 0; k < n_valves; k++)
    {
        for (int i = 0; i < n_valves; i++)
        {
            for (int j = 0; j < n_valves; j++)
            {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // get zero bitstring corresponding to # useful vaults
    string init = "";
    for (int x = 0; x < n_useful; x++)
    {
        init += "0";
        all_opened += "1";
    }

    for (auto u : valve_ids)
    {
        cout << "valve " << u.first << " has id " << u.second << endl;
    }
    // find max pressure
    int max_pres = find_max_pressure(0, valve_ids["AA"], init, dist);
    cout << max_pres << endl;
}

// recursive DP function
// 'opened' is a bitstring with n_useful bits
// bit i is 1 if the ith useful valve is opened, and 0 otherwise
int find_max_pressure(int time, int pos, string opened, int dist[60][60])
{

    // check if solution to this subproblem has been previously computed
    if (memo[time].count(opened) == 1)
    {
        return memo[time][opened];
    }
    else if (opened == all_opened)
    {
        return 0;
    }
    // otherwise, compute solution to this subproblem
    else
    {
        int max_pressure = 0;
        // iterate over all useful valves
        for (int next = 0; next < n_useful; next++)
        {
            // skip valves that are already open
            if (opened[next] == '1')
            {
                continue;
            }
            // for every unopened useful valve, ...
            else
            {
                // check if we can open it without exceeding the time limit
                int next_id = useful_valve_ids[next];
                int next_time = time + dist[pos][next_id] + 1;
                if (next_time >= STEPS)
                {
                    continue;
                }
                // if we can open it without exceeding the time limit, ...
                else
                {
                    // compute total pressure released by opening that valve next
                    valve next_valve = valves[next_id];
                    int next_pressure = (STEPS - next_time) * next_valve.rate;

                    // update the bitstring since this valve is now open
                    string *next_opened = new string(opened);
                    (*next_opened)[next] = '1';

                    // recursively compute max pressure
                    max_pressure = max(max_pressure, next_pressure + find_max_pressure(next_time, next_id, *next_opened, dist));
                }
            }
        }
        // memoize result and return
        if (memo[time].count(opened) != 1)
        {
            memo[time][opened] = 0;
        }
        memo[time][opened] = max_pressure;
        return max_pressure;
    }
}