#include <bits/stdc++.h>
using namespace std;
int main()
{
    int count = 0;
    string pair_string;
    while (cin >> pair_string)
    {
        // get start and end ranges of each pair
        char *first_range = strtok(&pair_string[0], ",");
        char *second_range = strtok(NULL, ",");
        int first_start = stoi(strtok(first_range, "-"));
        int first_end = stoi(strtok(NULL, "-"));
        int second_start = stoi(strtok(second_range, "-"));
        int second_end = stoi(strtok(NULL, "-"));

        if (first_start <= second_end && first_end >= second_end)
        {
            count += 1;
        }
        else if (second_start <= first_end && second_end >= first_end)
        {
            count += 1;
        }
    }
    cout << count << endl;
}
