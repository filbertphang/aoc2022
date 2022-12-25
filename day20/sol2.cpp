#include <bits/stdc++.h>
using namespace std;

const int N = 5000;

// store encryption key and the key mod (N-1)
const long KEY = 811589153;
const long KEY_MOD = KEY % (N - 1);

struct num
{
    int val;
    long true_val;
    num *prev;
    num *next;
};

int main()
{
    // construct circular doubly linked list from input
    num dll[N];
    num *zero;
    num *prev = &dll[N - 1];
    for (int i = 0; i < N; i++)
    {
        num *cur = new num();
        long tmp;
        cin >> tmp;
        // property: (a mod n) * (b mod n) = (ab) mod n
        cur->val = ((tmp % (N - 1)) * KEY_MOD) % (N - 1);
        // store true value for sum later
        cur->true_val = tmp;

        // assign pointers to previous and next element in list
        cur->prev = prev;
        cur->next = &dll[(i + 1) % N];
        dll[i] = *cur;
        prev = &dll[i];

        // store pointer to zero element
        if (cur->val == 0)
        {
            zero = &dll[i];
        }
    }

    // mix 10 times
    for (int x = 0; x < 10; x++)
    {

        for (int i = 0; i < N; i++)
        {
            // find how many spaces to jump forward
            int jump = dll[i].val;
            num *tar;
            if (jump < 0)
            {
                // any backwards jump can also be accomplished by
                // some corresponding forwards jump
                jump = (N - 1) + (jump % (N - 1));
            }
            else
            {
                jump = jump % (N - 1);
            }

            // minor optimization: skip if we do nothing
            if (jump == 0)
            {
                continue;
            }
            // else, find the target element to jump to
            else
            {
                num *cur = &dll[i];
                for (int j = 0; j < jump; j++)
                {
                    cur = cur->next;
                }
                tar = cur;
            }

            // connect previous and next element of the current element to each other
            num *prev_old = dll[i].prev;
            num *next_old = dll[i].next;
            prev_old->next = next_old;
            next_old->prev = prev_old;

            // connect previous and next element of the target element
            // to the current element
            num *prev_new = tar;
            num *next_new = tar->next;
            dll[i].prev = prev_new;
            prev_new->next = &dll[i];
            dll[i].next = next_new;
            next_new->prev = &dll[i];
        }

        num *tmp = zero;
        cout << "after " << x + 1 << " rounds:";
        for (int i = 0; i < N; i++)
        {
            cout << tmp->true_val << " ";
            tmp = tmp->next;
        }
        cout << "\n";
    }
    // display
    long sum = 0;
    num *tmp = zero;
    for (int i = 0; i < N; i++)
    {
        if (i == 1000 % N)
        {
            cout << "1000th number: " << tmp->true_val << "\n";
            sum += tmp->true_val;
        }
        if (i == 2000 % N)
        {
            cout << "2000th number: " << tmp->true_val << "\n";
            sum += tmp->true_val;
        }
        if (i == 3000 % N)
        {
            cout << "3000th number: " << tmp->true_val << "\n";
            sum += tmp->true_val;
        }
        tmp = tmp->next;
    }
    cout << "sum: " << sum << "\n";
    cout << "true sum: " << sum * KEY << "\n";
}