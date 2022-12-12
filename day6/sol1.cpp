#include <bits/stdc++.h>
using namespace std;
int main()
{
    list<char> queue;
    int count = 0;
    char c;
    // process character-by-character
    while (cin >> c)
    {
        count += 1;

        // maintain the most recent 4 characters in a queue (list)
        if (queue.size() == 4)
        {
            queue.pop_front();
        }
        queue.push_back(c);

        // get count of unique characters in the queue
        list<char> tmp(queue);
        tmp.sort();
        tmp.unique();

        // if all characters are unique, we've found the start-of-packet
        if (tmp.size() == 4)
        {
            cout << count << endl;
            break;
        }
    }
}
