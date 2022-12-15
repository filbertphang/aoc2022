#include <bits/stdc++.h>
using namespace std;

struct treeNode
{
    map<string, treeNode *> children;
    treeNode *parent;
    string name = "";
    long size = 0;
};

// post-order traversal of tree
int traverse(treeNode *node, vector<long> *sizes)
{
    long size = node->size;

    // add total size of all children to current node
    for (pair<string, treeNode *> element : node->children)
    {
        size += traverse(element.second, sizes);
    }

    // store current size in vector
    sizes->push_back(size);
    return size;
}

int main()
{
    // init tree
    string command;
    string current_dir;
    treeNode root;
    root.name = "/";
    treeNode *current = &root;

    // parse directory tree
    while (cin >> command)
    {
        // check for cd and ls commands
        if (command == "$")
        {
            cin >> command;
            // cd
            if (command == "cd")
            {
                cin >> current_dir;
                if (current_dir == "/")
                {
                }
                // traverse back up to parent
                else if (current_dir == "..")
                {
                    current = current->parent;
                }
                // set current to the correct child
                else
                {
                    current = current->children[current_dir];
                }
            }
            // nothing needed if command is ls
        }
        // check for directories
        else if (command == "dir")
        {
            string name;
            cin >> name;

            // create a new treeNode corresponding to that directory
            treeNode *tmp = new treeNode();
            tmp->name = name;
            tmp->parent = current;

            // add it as a child of the current directory
            current->children[name] = tmp;
        }
        // check for files
        else
        {
            // add file size to total size of current directory
            long size = stol(command);
            current->size += size;
            cin >> command;
        }
    }

    // traverse tree and get size of root directory
    vector<long> sizes;
    long max = traverse(&root, &sizes);

    // find the smallest element >= min required space to free
    sort(sizes.begin(), sizes.end());
    long diff = 30000000 - (70000000 - max);
    auto lower = lower_bound(sizes.begin(), sizes.end(), diff);
    cout << *lower << endl;
}
