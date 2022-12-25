#include <bits/stdc++.h>
using namespace std;

// it's a monkey!
struct monkey
{
    string op1;
    string op2;
    char opn;
    long val = -1;
};

map<string, monkey> mks;

// recursively yell to compute value of root monkey
long yell(string name)
{
    monkey mk = mks[name];
    // memoize monkey values for Extra Efficiency
    if (mk.val != -1)
    {
        return mk.val;
    }
    // if not stored, compute monkey value
    else
    {
        // recursively get values of 2 dependent monkeys
        long val1 = yell(mk.op1);
        long val2 = yell(mk.op2);
        long result;

        // compute result
        if (mk.opn == '-')
        {
            result = val1 - val2;
        }
        else if (mk.opn == '+')
        {
            result = val1 + val2;
        }
        else if (mk.opn == '*')
        {
            result = val1 * val2;
        }
        else if (mk.opn == '/')
        {
            result = val1 / val2;
        }
        // memoize and return
        mk.val = result;
        return result;
    }
};

int main()
{
    string line;
    regex_token_iterator<string::iterator> rend;

    // regex patterns
    regex num_pattern("[0-9]+");
    regex name_pattern("[a-z]{4}");
    regex op_pattern("[+-/*]");

    while (!cin.eof())
    {
        getline(cin, line);

        // find monkey name
        regex_token_iterator<string::iterator> name_match(line.begin(), line.end(), name_pattern);
        string name = *(name_match++);
        monkey *mk = new monkey();

        // check if monkey's job is a number or an operation
        // if it's a number, parse and store it
        if (name_match == rend)
        {
            regex_token_iterator<string::iterator> num_match(line.begin(), line.end(), num_pattern);
            mk->val = stol(*num_match);
        }
        // if it's an operation, parse and store that too
        else
        {
            mk->op1 = *(name_match++);
            mk->op2 = *(name_match);
            regex_token_iterator<string::iterator> op_match(line.begin(), line.end(), op_pattern);
            string tmp = *op_match;
            mk->opn = tmp[0];
        }
        mks[name] = *mk;
    }

    // ahhhhh!
    long sol = yell("root");
    cout << sol << "\n";
}
