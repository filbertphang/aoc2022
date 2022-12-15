#include <bits/stdc++.h>
using namespace std;

const int YLEVEL = 2000000;

int main()
{
    set<int> no_beacon; // x-values at y=YLEVEL where distress beacon cannot exist
    set<int> beacon;    // x-values at y=YLEVEL that are occupied by other beacons

    // regex pattern
    regex num("-?[0-9]+");
    regex_token_iterator<string::iterator> rend;

    // iterate over each sensor
    string line;
    while (!cin.eof())
    {
        // parse sensor and beacon coordinates
        getline(cin, line);
        regex_token_iterator<string::iterator> matches(line.begin(), line.end(), num);
        int sx = stoi(*matches++);
        int sy = stoi(*matches++);
        int bx = stoi(*matches++);
        int by = stoi(*matches++);

        // compute distance from sensor to beacon and sensor to y=YLEVEL
        int dist_to_beacon = abs(sx - bx) + abs(sy - by);
        int dist_to_2m = abs(sy - YLEVEL);

        // add positions at y=YLEVEL where distress beacon cannot exist
        for (int i = 0; i <= dist_to_beacon - dist_to_2m; i++)
        {
            no_beacon.insert(sx + i);
            no_beacon.insert(sx - i);
        }

        // keep track of positions occupied by other beacons at y=YLEVEL
        if (by == YLEVEL)
        {
            beacon.insert(bx);
        }
    }

    // remove positions where there are other beacons
    for (int i : beacon)
    {
        no_beacon.erase(i);
    }

    cout << no_beacon.size() << endl;
}
