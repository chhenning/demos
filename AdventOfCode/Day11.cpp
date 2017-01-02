#include "stdafx.h"

struct situation;

struct situation
{
    situation()
    : elevator(min_floor)
    {}

    void add_item(std::string name, int floor)
    {
        items.push_back({name, floor});
    }

    bool operator==(const situation& other) const
    {
        bool items_equal = equal(items.begin(), items.end(), other.items.begin(), other.items.end());

        return (elevator == other.elevator) && items_equal;
    }

    std::vector<std::pair<std::string,int>> get_moveable_items() const
    {
        std::vector<std::pair<std::string,int>> moveable_items;

        for(const auto& i : items)
        {
            if(i.second == elevator)
            {
                moveable_items.push_back(i);
            }
        }

        return moveable_items;
    }

    bool finished() const
    {
        for(const auto& i : items)
        {
            if(i.second < max_floor)
            {
                return false;
            }
        }

        return true;
    }

    static const int max_floor = 4;
    static const int min_floor = 1;

    int elevator;
    std::vector<std::pair<std::string,int>> items;
};

namespace std
{
    template<>
    struct hash<situation>
    {
        std::size_t operator()(const situation& s) const
        {
            using std::size_t;
            using std::hash;
            
            size_t items_hash = 0;

            for(const auto& i : s.items)
            {
                items_hash ^= hash<string>()(i.first) ^ hash<int>()(i.second);
            }
            
            return (hash<int>{}(s.elevator) ^ items_hash);
        }

    };
}

using namespace std;

vector<situation> generate(const situation& start)
{
    vector<situation> new_situations;

    // 1. find all elements on same floor as the elevator
    auto moveable_items = start.get_moveable_items();

    // @todo only allows up to two items into an elevator

    // 2. Move up elevator by one
    if(start.elevator < situation::max_floor)
    {
        int num_combinations = (1 << moveable_items.size()) - 1;

        for(int i = 1; i <= num_combinations; ++i)
        {
            situation s;
            s.elevator = start.elevator + 1;

            for(int j = 0; j < moveable_items.size(); ++j)
            {
                if(i & (1 << j))
                {
                    const string& name = moveable_items[j].first;
                    s.add_item(name, s.elevator);
                }
            }

            new_situations.push_back(s);
        }
    }

    // 3. Move down elevator by one
    if(start.elevator > situation::min_floor)
    {
        int num_combinations = (1 << moveable_items.size()) - 1;

        for(int i = 1; i <= num_combinations; ++i)
        {
            situation s;
            s.elevator = start.elevator - 1;

            for(int j = 0; j < moveable_items.size(); ++j)
            {
                if(i & (1 << j))
                {
                    const string& name = moveable_items[j].first;
                    s.add_item(name, s.elevator);
                }
            }

            new_situations.push_back(s);
        }
    }

    return new_situations;
}

void run_day_11()
{
    unordered_map<situation,vector<situation>> decision_tree;

    situation start;
    start.add_item("G", situation::min_floor);
    start.add_item("M", situation::min_floor);

    decision_tree[start];

    while(true)
    {
        for(const auto& s : decision_tree)
        {
            if(s.second.size() == 0)
            {
                auto next_moves = generate(s.first);

                for(const auto& m: next_moves)
                {
                    if(decision_tree[m].size() > 0) { continue; }

                    decision_tree[s.first].push_back(m);
                    decision_tree[m];
                }
            }
        }


        bool success = false;

        // look if a solution is available
        for(const auto& s : decision_tree)
        {
            if(s.first.finished())
            {
                success = true;
            }
        }

        if(success)
        {
            break;        
        }
    }


/*
    vector<string> items = {"G", "M"};

    int num_combinations = (1 << items.size()) - 1;

    for(int i = 1; i <= num_combinations; ++i)
    {
        for(int j = 0; j < items.size(); ++j)
        {
            if(i & (1 << j))
            {
                cout << items[j];
            }
        }

        cout << endl;
    }
*/
}