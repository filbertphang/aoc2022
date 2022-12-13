#include <bits/stdc++.h>
using namespace std;

struct monkey
{
    vector<int> items;
    char operation;
    string operand;
    int test;
    int if_true;
    int if_false;
};

int main()
{
    monkey monkeys[8];
    // string parsing in c++ is a nightmare
    for (int i = 0; i < 8; i++)
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
        vector<int> *items = new vector<int>();
        char *tok_result = strtok(item_str, ",");
        int item_id;
        while (tok_result != NULL)
        {
            item_id = stoi(tok_result);
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

        cout << monkeys[i].operation << " " << monkeys[i].operand << " " << monkeys[i].test << " " << monkeys[i].if_true << " " << monkeys[i].if_false << endl;
    }
}
