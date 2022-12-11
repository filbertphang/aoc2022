#include <bits/stdc++.h>
using namespace std;
int main()
{
    // min PQ
    priority_queue<int, vector<int>, greater<int>> pq;
    int cur_sum = 0;
    string input;
    while (!cin.eof())
    {
        getline(cin, input);
        if (input.empty())
        {
            // if there are exactly elements in the PQ,
            if (pq.size() == 3)
            {
                // replace the smallest element if the current sum is larger
                if (pq.top() < cur_sum)
                {
                    pq.pop();
                    pq.push(cur_sum);
                }
            }
            // else just push to PQ directly
            else
            {
                pq.push(cur_sum);
            }
            cur_sum = 0;
        }
        else
        {
            int cur = stoi(input);
            cur_sum += cur;
        }
    }
    // get calorie sum of top 3 goblins
    int result = 0;
    result += pq.top();
    pq.pop();
    result += pq.top();
    pq.pop();
    result += pq.top();
    pq.pop();
    cout << result << endl;
}