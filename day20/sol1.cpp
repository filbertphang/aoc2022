#include <bits/stdc++.h>
using namespace std;

const int N = 5000;
// const int N = 7;

struct num
{
    int val;
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
        cin >> cur->val;

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

    // mix once
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
    // display
    int sum = 0;
    num *tmp = zero;
    for (int i = 0; i < N; i++)
    {
        if (i == 1000 % N)
        {
            cout << "1000th number: " << tmp->val << "\n";
            sum += tmp->val;
        }
        if (i == 2000 % N)
        {
            cout << "2000th number: " << tmp->val << "\n";
            sum += tmp->val;
        }
        if (i == 3000 % N)
        {
            cout << "3000th number: " << tmp->val << "\n";
            sum += tmp->val;
        }
        tmp = tmp->next;
    }
    cout << "sum: " << sum << "\n";
}