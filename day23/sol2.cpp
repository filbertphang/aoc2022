#include <bits/stdc++.h>
using namespace std;

const int SIZE = 73;
const int PAD = 30;
// const int SIZE = 7;
// const int PAD = 3;

struct Elf
{
    pair<int, int> pos;
    pair<int, int> next;
};

// directions
// 0,1,2,3 = north, south, east, west
deque<int> directions = {0, 1, 2, 3};

// comparator for sorting
bool cmp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
{
    return a.first < b.first;
}

// debug function
// displays the positions in v on a grid
void map_vec(vector<pair<int, int>> v)
{
    char grid[2 * PAD + SIZE][2 * PAD + SIZE];
    for (int i = 0; i < 2 * PAD + SIZE; i++)
    {
        for (int j = 0; j < 2 * PAD + SIZE; j++)
        {
            grid[i][j] = '.';
        }
    }

    for (pair<int, int> vv : v)
    {
        grid[vv.first][vv.second] = '#';
    }

    for (int i = 0; i < 2 * PAD + SIZE; i++)
    {
        for (int j = 0; j < 2 * PAD + SIZE; j++)
        {
            cout << grid[i][j] << "";
        }
        cout << "\n";
    }
}

int main()
{
    // init grid
    map<pair<int, int>, bool> grid;

    // init elves (row, col)
    vector<Elf> elves;

    // parse input
    string line;
    for (int i = 0; i < SIZE; i++)
    {
        getline(cin, line);
        for (int j = 0; j < SIZE; j++)
        {
            if (line[j] == '#')
            {
                Elf *e = new Elf();
                e->pos = pair<int, int>(i + PAD, j + PAD);
                elves.push_back(*e);
                grid[e->pos] = true;
            }
        }
    }

    // move elves
    vector<pair<pair<int, int>, int>> next_moves;
    int step = 0;
    bool term = false;
    while (!term)
    {
        term = true;
        // suggest directions
        for (int i = 0; i < elves.size(); i++)
        {
            Elf *elf = &elves[i];
            pair<int, int> next_move = elf->pos;

            // check for any adjacent elves
            bool has_adjacent = false;
            for (int r = elf->pos.first - 1; r <= elf->pos.first + 1; r++)
            {
                for (int c = elf->pos.second - 1; c <= elf->pos.second + 1; c++)
                {
                    if (r == elf->pos.first && c == elf->pos.second)
                    {
                        continue;
                    }
                    if (grid.count(pair<int, int>(r, c)) == 1)
                    {
                        has_adjacent = true;
                    }
                }
            }

            // check if elf has other elves adjacent to it
            // if no adj elves, we can skip moving
            if (has_adjacent)
            {
                term = false;
                // suggest a direction to move in
                for (int dir : directions)
                {
                    bool can_move = true;

                    // north
                    if (dir == 0)
                    {
                        for (int cp = elf->pos.second - 1; cp <= elf->pos.second + 1; cp++)
                        {
                            pair<int, int> p = pair<int, int>(elf->pos.first - 1, cp);
                            if (grid.count(p) == 1)
                            {
                                can_move = false;
                            }
                        }
                        if (can_move)
                        {
                            next_move.first -= 1;
                            break;
                        }
                        continue;
                    }
                    // south
                    else if (dir == 1)
                    {
                        for (int cp = elf->pos.second - 1; cp <= elf->pos.second + 1; cp++)
                        {
                            pair<int, int> p = pair<int, int>(elf->pos.first + 1, cp);
                            if (grid.count(p) == 1)
                            {
                                can_move = false;
                            }
                        }
                        if (can_move)
                        {
                            next_move.first += 1;
                            break;
                        }
                        continue;
                    }
                    // east
                    else if (dir == 3)
                    {
                        for (int rp = elf->pos.first - 1; rp <= elf->pos.first + 1; rp++)
                        {
                            pair<int, int> p = pair<int, int>(rp, elf->pos.second + 1);
                            if (grid.count(p) == 1)
                            {
                                can_move = false;
                            }
                        }
                        if (can_move)
                        {
                            next_move.second += 1;
                            break;
                        }
                        continue;
                    }
                    // west
                    else if (dir == 2)
                    {
                        for (int rp = elf->pos.first - 1; rp <= elf->pos.first + 1; rp++)
                        {
                            pair<int, int> p = pair<int, int>(rp, elf->pos.second - 1);
                            if (grid.count(p) == 1)
                            {
                                can_move = false;
                            }
                        }
                        if (can_move)
                        {
                            next_move.second -= 1;
                            break;
                        }
                        continue;
                    }
                }
            }

            // note down the coordinates of the elf's next move
            // based on the direction they suggest
            elf->next = next_move;
            next_moves.push_back(pair<pair<int, int>, int>(next_move, i));
        }

        // check direction conflicts and move
        sort(next_moves.begin(), next_moves.end(), cmp);
        for (int i = 0; i < next_moves.size(); i++)
        {
            // this move conflicts with another elf, so we don't move all elves
            if (i < next_moves.size() - 1 && next_moves[i].first == next_moves[i + 1].first)
            {
                while (next_moves[i].first == next_moves[i + 1].first && i < next_moves.size() - 1)
                {
                    i += 1;
                }
            }
            // this move does not conflict, so we move
            else
            {
                int elf_id = next_moves[i].second;
                grid.erase(elves[elf_id].pos);
                grid[elves[elf_id].next] = true;
                elves[elf_id].pos = elves[elf_id].next;
            }
        }

        // cycle directions
        directions.push_back(directions.front());
        directions.pop_front();
        next_moves.clear();
        step += 1;
    }

    cout << step << "\n";
}
