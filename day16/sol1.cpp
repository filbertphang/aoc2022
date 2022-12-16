#include <bits/stdc++.h>
using namespace std;

struct valve
{
    int rate;
    vector<string> tunnels;
};

int main()
{
    string line;

    // storage
    map<string, int> valve_ids;
    vector<valve> valves;
    vector<int> useful_valve_ids;

    // regex stuff
    regex num("[0-9]+");
    regex name("[A-Z]{2}");
    regex_token_iterator<string::iterator> rend;

    int valve_id = 0;
    while (!cin.eof())
    {
        // parse input
        getline(cin, line);
        valve *cur_valve = new valve();
        regex_token_iterator<string::iterator> num_match(line.begin(), line.end(), num);
        cur_valve->rate = stoi(*num_match);

        regex_token_iterator<string::iterator> name_match(line.begin(), line.end(), name);
        string valve_name = *name_match++;
        vector<string> *tunnels = new vector<string>();
        while (name_match != rend)
        {
            tunnels->push_back(*name_match++);
        }
        cur_valve->tunnels = *tunnels;

        cout << "valve " << valve_name << " has id: " << valve_id << endl;

        valve_ids[valve_name] = valve_id;
        valves.push_back(*cur_valve);

        if (cur_valve->rate > 0)
        {
            useful_valve_ids.push_back(valve_id);
        }

        valve_id += 1;
    }

    int n_valves = valve_id;

    // init distance array with a large value,
    // and set initial distances between adjacent valves to 1
    int dist[n_valves][n_valves] = {0};
    for (int row = 0; row < n_valves; row++)
    {
        for (int col = 0; col < n_valves; col++)
        {
            dist[row][col] = n_valves + 100;
        }
        for (string vname : valves[row].tunnels)
        {
            int vid = valve_ids[vname];
            dist[l][vid] = 1;
            dist[vid][l] = 1;
        }
    }

    // use Floyd-Warshall to compute all-pairs shortest path
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
}
