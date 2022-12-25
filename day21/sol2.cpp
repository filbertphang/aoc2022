#include <bits/stdc++.h>
using namespace std;

// it's a monkey!
struct monkey
{
    string op1;
    string op2;
    char opn;
    long val = -1;
    int human = -1;
};

map<string, monkey *> mks;

// does monkey math
long do_op(long val1, long val2, char opn)
{
    long result;
    if (opn == '-')
    {
        result = val1 - val2;
    }
    else if (opn == '+')
    {
        result = val1 + val2;
    }
    else if (opn == '*')
    {
        result = val1 * val2;
    }
    else if (opn == '/')
    {
        result = val1 / val2;
    }
    return result;
}

// determine whether the human is in the left, right, or no subtree of the monkey
// 0: not in subtree
// 1: in left subtree
// 2: in right subtree
// returns whether or not the human was found in the subtree rooted at that monkey
bool find_human(string name)
{
    monkey *mk = mks[name];
    // monkeys with a stored value are leaf nodes
    // i.e. human cannot be in either subtree (since both subtrees are empty)
    if (mk->val != -1)
    {
        mk->human = 0;
        return false;
    }
    // human is a direct child of this node
    // identify and note down accordingly
    else if (mk->op1 == "humn")
    {
        mk->human = 1;
        return true;
    }
    else if (mk->op2 == "humn")
    {
        mk->human = 2;
        return true;
    }
    // recursively determine which subtree the human is in
    else
    {
        bool human1 = find_human(mk->op1);
        bool human2 = find_human(mk->op2);
        // human is in left or right subtree
        if (human1)
        {
            mk->human = 1;
            return true;
        }
        else if (human2)
        {
            mk->human = 2;
            return true;
        }
        // human is in neither subtree
        else
        {
            mk->human = 0;
            return false;
        }
    }
}

// yell to compute a monkey's value (and all monkeys in its subtree)
long yell(string name)
{
    monkey *mk = mks[name];
    // memoize monkey values for Extra Efficiency
    if (mk->val != -1)
    {
        return mk->val;
    }
    // if not stored, compute monkey value
    else
    {
        // recursively get values of 2 dependent monkeys
        long val1 = yell(mk->op1);
        long val2 = yell(mk->op2);

        // compute, memoize, and return
        long result = do_op(val1, val2, mk->opn);
        mk->val = result;
        return result;
    }
}

// compute the human's value
long find_human_value(string name, long target)
{
    // base case: we reach the human
    if (name == "humn")
    {
        return target;
    }

    // idea: human can only be in one of the monkey's two subtrees
    // compute the value yelled by the monkey in the other subtree,
    // then work backwards to determine what value should be obtained by
    // the monkey in the human subtree
    monkey *mk = mks[name];
    long other_val;
    long new_target;
    string human_branch;
    if (mk->human == 1)
    {
        human_branch = mk->op1;
        other_val = yell(mk->op2);
        new_target = other_val;
        // target = human_branch OPN other_val
        if (mk->opn == '+')
        {
            new_target = do_op(target, other_val, '-');
        }
        else if (mk->opn == '-')
        {
            new_target = do_op(target, other_val, '+');
        }
        else if (mk->opn == '*')
        {
            new_target = do_op(target, other_val, '/');
        }
        else if (mk->opn == '/')
        {
            new_target = do_op(target, other_val, '*');
        }
    }
    else if (mk->human == 2)
    {
        human_branch = mk->op2;
        other_val = yell(mk->op1);
        new_target = other_val;
        // target = other_val OPN human_branch
        if (mk->opn == '+')
        {
            new_target = do_op(target, other_val, '-');
        }
        else if (mk->opn == '-')
        {
            new_target = do_op(other_val, target, '-');
        }
        else if (mk->opn == '*')
        {
            new_target = do_op(target, other_val, '/');
        }
        else if (mk->opn == '/')
        {
            new_target = do_op(other_val, target, '/');
        }
    }
    return find_human_value(human_branch, new_target);
}

int main()
{
    string line;
    regex_token_iterator<string::iterator> rend;

    // regex patterns
    regex num_pattern("[0-9]+");
    regex name_pattern("[a-z]{4}");
    regex op_pattern("[+-/*]");

    // parse input
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

        if (name == "root")
        {
            mk->opn = '=';
        }
        mks[name] = mk;
    }

    // get the human's position relative to all nodes
    find_human("root");

    // find the human's value
    // (the first target value is ignored since root's operation is =)
    long human_value = find_human_value("root", 0);
    cout << human_value << "\n";
}
