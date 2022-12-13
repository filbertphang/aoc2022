#include <bits/stdc++.h>
using namespace std;

const int N = 8;
long MOD = 1;

struct monkey
{
    list<long> items;
    char operation;
    string operand;
    int test;
    int if_true;
    int if_false;
    long inspections = 0;
};

/*
idea: we use the following properties of modular arithmetic
    1) a mod n + b mod n = (a+b) mod n
    2) a mod n * b mod n = (a*b) mod n
    3) (a mod n) mod p = a mod p, if p divides n
       i.e. if n % p == 0

    since worry values can now get ridiculously large, we should
    modulo everything by a certain value to keep it reasonably sized.
    since we want to property (3) to hold for the divisibility tests
    of all the monkeys, we must choose a number such that all test values
    divide that number.
    trivially, we can obtain that number by multiplying all the test values
    together.
*/
int inspect(monkey *monkey, long *item)
{
    monkey->inspections += 1;
    long worry = *item;
    long op;
    if (monkey->operand == "old")
    {
        op = *item;
    }
    else
    {
        op = stoi(monkey->operand);
    }

    // calculate worry from inspection
    if (monkey->operation == '+')
    {
        worry = (worry % MOD) + (op % MOD);
    }
    else
    {
        worry = (worry % MOD) * (op % MOD);
    }

    // update new worry value of item
    *item = worry;

    // decide which monkey to throw to
    if (worry % monkey->test == 0)
    {
        return monkey->if_true;
    }
    else
    {
        return monkey->if_false;
    }
}

int main()
{
    monkey monkeys[N];
    // string parsing in c++ is a nightmare
    for (int i = 0; i < N; i++)
    {
        // create monkey
        monkey *cur = new monkey();

        // parse monkey number
        string dummy;
        string line;
        int monkey_id;
        cin >> dummy >> monkey_id;
        getline(cin, line);

        // parse starting items
        getline(cin, line);
        strtok(&line[0], ":");
        char *item_str = strtok(NULL, ":");
        list<long> *items = new list<long>();
        char *tok_result = strtok(item_str, ",");
        long item_id;
        while (tok_result != NULL)
        {
            item_id = stol(tok_result);
            items->push_back(item_id);
            tok_result = strtok(NULL, ",");
        }
        cur->items = *items;

        // parse operation
        getline(cin, line);
        cur->operation = line[23];
        char *operand = strtok(&line[0], " ");
        string last;
        while (operand != NULL)
        {
            last = operand;
            operand = strtok(NULL, " ");
        }
        cur->operand = last;

        // parse test
        getline(cin, line);
        char *test = strtok(&line[0], " ");
        while (test != NULL)
        {
            last = test;
            test = strtok(NULL, " ");
        }
        cur->test = stoi(last);
        MOD *= stoi(last);

        // parse if true and false
        getline(cin, line);
        char *condition = strtok(&line[0], " ");
        while (condition != NULL)
        {
            last = condition;
            condition = strtok(NULL, " ");
        }
        cur->if_true = stoi(last);

        getline(cin, line);
        condition = strtok(&line[0], " ");
        while (condition != NULL)
        {
            last = condition;
            condition = strtok(NULL, " ");
        }
        cur->if_false = stoi(last);

        // store monkey and read blank line
        monkeys[i] = *cur;
        getline(cin, line);
    }

    // repeat for 10000 steps
    for (int j = 0; j < 10000; j++)
    {
        // handle behaviour for each monkey
        for (int m = 0; m < N; m++)
        {
            // throw items until that monkey has no items left
            while (!monkeys[m].items.empty())
            {
                // get top item
                long item = monkeys[m].items.front();
                monkeys[m].items.pop_front();

                // inspect top item
                int target = inspect(&monkeys[m], &item);

                // throw top item to next monkey
                monkeys[target].items.push_back(item);
            }
        }

        // debug print statements
        /*
        cout << "===== after round " << j << " =====" << endl;
        for (int m = 0; m < N; m++)
        {
            ;
            cout << m << ": ";
            for (int it : monkeys[m].items)
            {
                cout << it << " ";
            }
            cout << endl;
        }
        cout << endl;
        */
    }

    // count number of inspections
    long inspections[N];
    for (int k = 0; k < N; k++)
    {
        inspections[k] = monkeys[k].inspections;
    }
    sort(inspections, inspections + N);

    // compute monkey business... heh
    long long monkey_business = inspections[N - 2] * inspections[N - 1];
    cout << monkey_business << endl;
}
