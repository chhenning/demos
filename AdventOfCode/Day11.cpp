#include "stdafx.h"

struct situation;

struct situation
{
    situation()
    : elevator(min_floor)
    {}

    void add_item(string name, int floor)
    {
        items.push_back({ name, floor });
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

    bool finished()
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
                    s.items.push_back(moveable_items[j]);
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
                    s.items.push_back(moveable_items[j]);
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

    auto next_situations = generate(start);

    for(const auto& s : next_situations)
    {
        if(decision_tree.find(s) == decision_tree.end())
        {
            decision_tree[start].push_back(s);
            decision_tree[s].clear();
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