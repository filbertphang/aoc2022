#include <bits/stdc++.h>
using namespace std;

struct sensor
{
    int x;
    int y;
    int range;
};

long long UPPER = 4000000;

int main()
{
    // regex pattern
    regex num("-?[0-9]+");
    regex_token_iterator<string::iterator> rend;

    // iterate over each sensor
    string line;
    vector<sensor> sensors;
    while (!cin.eof())
    {
        // parse sensor and beacon coordinates
        getline(cin, line);
        regex_token_iterator<string::iterator> matches(line.begin(), line.end(), num);
        int sx = stoi(*matches++);
        int sy = stoi(*matches++);
        int bx = stoi(*matches++);
        int by = stoi(*matches++);

        // compute distance from sensor to beacon
        int dist = abs(sx - bx) + abs(sy - by);

        // add sensor data (x, y, range) into sensors list
        sensor *cur_sensor = new sensor();
        cur_sensor->x = sx;
        cur_sensor->y = sy;
        cur_sensor->range = dist;
        sensors.push_back(*cur_sensor);
    }

    // find tuning frequency
    long long tuning_freq;
    for (int y = 0; y <= UPPER; y++)
    {
        for (int x = 0; x <= UPPER; x++)
        {
            bool in_range = false;
            for (sensor s : sensors)
            {
                int dist_from_centre = abs(x - s.x) + abs(y - s.y);
                if (dist_from_centre <= s.range)
                {
                    // increment x to the end of this sensor's range
                    x = s.x + (s.range - abs(y - s.y));
                    in_range = true;
                    break;
                }
            }
            if (in_range)
            {
                in_range = false;
            }
            else
            {
                tuning_freq = (x * UPPER) + y;
                cout << "x: " << x << ", y: " << y << endl;
                cout << tuning_freq << endl;
                break;
            }
        }
    }
}
