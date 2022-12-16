#include <bits/stdc++.h>
using namespace std;

struct valve
{
    string name;
    int rate;
    vector<string> tunnels;
};

map<string, valve> valves;

int main()
{
    string line;

    // regex stuff
    regex num("[0-9]+");
    regex name("[A-Z]{2}");
    regex_token_iterator<string::iterator> rend;

    while (!cin.eof())
    {
        // parse input
        getline(cin, line);
        valve *cur_valve = new valve();
        regex_token_iterator<string::iterator> num_match(line.begin(), line.end(), num);
        cur_valve->rate = stoi(*num_match);

        regex_token_iterator<string::iterator> name_match(line.begin(), line.end(), name);
        cur_valve->name = *name_match++;
        vector<string> *tunnels = new vector<string>();
        while (name_match != rend)
        {
            tunnels->push_back(*name_match++);
        }
        cur_valve->tunnels = *tunnels;

        valves[cur_valve->name] = *cur_valve;
    }

    for (const auto &pv : valves)
    {
        valve v = pv.second;
        cout << v.name << ": " << v.rate << ". ";
        for (string s : v.tunnels)
        {
            cout << s << ", ";
        }
        cout << endl;
    }
}
