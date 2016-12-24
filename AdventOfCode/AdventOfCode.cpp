
// http://adventofcode.com/

#include "stdafx.h"

#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

///
/// Start at (0,0) and walk along North, East, South, and West according to current orientation.
/// Once arrived at the endpoint calculate the distance from current pos to (0,0)
///
void No_Time_For_A_Taxi_Cab()
{
    //string data = "R2, L3";
    //string data = "R2, R2, R2";
    //string data = "R5, L5, R5, R3";
    //string data = "R23, L3";
    string data = "L3, R1, L4, L1, L2, R4, L3, L3, R2, R3, L5, R1, R3, L4, L1, L2, R2, R1, L4, L4, R2, L5, R3, R2, R1, L1, L2, R2, R2, L1, L1, R2, R1, L3, L5, R4, L3, R3, R3, L5, L190, L4, R4, R51, L4, R5, R5, R2, L1, L3, R1, R4, L3, R1, R3, L5, L4, R2, R5, R2, L1, L5, L1, L1, R78, L3, R2, L3, R5, L2, R2, R4, L1, L4, R1, R185, R3, L4, L1, L1, L3, R4, L4, L1, R5, L5, L1, R5, L1, R2, L5, L2, R4, R3, L2, R3, R1, L3, L5, L4, R3, L2, L4, L5, L4, R1, L1, R5, L2, R4, R2, R3, L1, L1, L4, L3, R4, L3, L5, R2, L5, L1, L1, R2, R3, L5, L3, L2, L1, L4, R4, R4, L2, R3, R1, L2, R1, L2, L2, R3, R3, L1, R4, L5, L3, R4, R4, R1, L2, L5, L3, R1, R4, L2, R5, R4, R2, L5, L3, R4, R1, L1, R5, L3, R1, R5, L2, R1, L5, L2, R2, L2, L3, R3, R3, R1";

    int x = 0;
    int y = 0;

    int orientation = 0;

    string num = "";

    for (int i = 0; i < data.length(); ++i)
    {
        char c = data[i];

        if (c == 'R')
        {
            orientation = ((orientation + 1) < 4) ? orientation + 1 : 0;
        }
        else if (c == 'L')
        {
            orientation = ((orientation - 1) >= 0) ? orientation - 1 : 3;
        }
        else if (c == ' ')
        {
            continue;
        }
        else if (c >= '0' && c <= '9')
        {
            num += c;
        }


        if (c == ',' || ((i + 1) == data.length()))
        {
            int steps = atoi(num.c_str());
            num.clear();

            switch (orientation)
            {
            case 0: { y += steps; break; }

            case 1: { x += steps; break; }

            case 2: { y -= steps; break; }

            case 3: { x -= steps; break; }
            }
        }
    }

    int distance = abs(x) + abs(y);

    cout << distance << endl;
}


///
/// Similar to part one but record each pos. For each new pos find if such pos already exists, if so we are done. 
/// Calculate distance to (0,0) and return.
///
void No_Time_For_A_Taxi_Cab__Part_2()
{
    //string data = "R2, L3";
    //string data = "R2, R2, R2";
    //string data = "R5, L5, R5, R3";
    //string data = "R23, L3";
    //string data = "R8, R4, R4, R8";
    string data = "L3, R1, L4, L1, L2, R4, L3, L3, R2, R3, L5, R1, R3, L4, L1, L2, R2, R1, L4, L4, R2, L5, R3, R2, R1, L1, L2, R2, R2, L1, L1, R2, R1, L3, L5, R4, L3, R3, R3, L5, L190, L4, R4, R51, L4, R5, R5, R2, L1, L3, R1, R4, L3, R1, R3, L5, L4, R2, R5, R2, L1, L5, L1, L1, R78, L3, R2, L3, R5, L2, R2, R4, L1, L4, R1, R185, R3, L4, L1, L1, L3, R4, L4, L1, R5, L5, L1, R5, L1, R2, L5, L2, R4, R3, L2, R3, R1, L3, L5, L4, R3, L2, L4, L5, L4, R1, L1, R5, L2, R4, R2, R3, L1, L1, L4, L3, R4, L3, L5, R2, L5, L1, L1, R2, R3, L5, L3, L2, L1, L4, R4, R4, L2, R3, R1, L2, R1, L2, L2, R3, R3, L1, R4, L5, L3, R4, R4, R1, L2, L5, L3, R1, R4, L2, R5, R4, R2, L5, L3, R4, R1, L1, R5, L3, R1, R5, L2, R1, L5, L2, R2, L2, L3, R3, R3, R1";

    int x = 0;
    int y = 0;

    vector<pair<int,int>> pos;
    pos.push_back(pair<int,int>(x,y));

    int orientation = 0;

    string num = "";

    for (int i = 0; i < data.length(); ++i)
    {
        char c = data[i];

        if (c == 'R')
        {
            orientation = ((orientation + 1) < 4) ? orientation + 1 : 0;
        }
        else if (c == 'L')
        {
            orientation = ((orientation - 1) >= 0) ? orientation - 1 : 3;
        }
        else if (c == ' ')
        {
            continue;
        }
        else if (c >= '0' && c <= '9')
        {
            num += c;
        }


        if (c == ',' || ((i + 1) == data.length()))
        {
            int steps = atoi(num.c_str());
            num.clear();

            for (int s = 0; s < steps; ++s)
            {
                switch (orientation)
                {
                    case 0: { y++; break; }

                    case 1: { x++; break; }

                    case 2: { y--; break; }

                    case 3: { x--; break; }
                }

                auto new_pos = pair<int, int>(x, y);

                for (int p = 0; p < pos.size(); ++p)
                {
                    auto a = pos[p];

                    if (a == new_pos)
                    {
                        int distance = abs(x) + abs(y);
                        cout << distance << endl;

                        return;
                    }
                }

                pos.push_back(pair<int, int>(x, y));
            }
        }
    }
}


void advance(pair<int,int>& pos, int x, int y)
{
    pos.first += x;
    pos.second += y;

    if (pos.first < 0) { pos.first = 0; }
    if (pos.first > 2) { pos.first = 2; }

    if (pos.second < 0) { pos.second = 0; }
    if (pos.second > 2) { pos.second = 2; }

}

void advance(const vector<vector<char>>& keypad, pair<int,int>& pos, int x, int y)
{
    assert(keypad[pos.second][pos.first] != '0');

    if(    (pos.second + y) >= 0 
        && (pos.first + x) >= 0 
        && (pos.second + y) < keypad.size()
        && (pos.first + x) < keypad.size()
        && keypad[pos.second + y][pos.first + x] != '0'
        )
    {
        pos.first += x;
        pos.second += y;
    }
    else
    {
        // cannot move
    }
}

void Bathroom_Security()
{
    vector<vector<int>> Keypad = {
        { 1, 2, 3 }, 
        { 4, 5, 6 },
        { 7, 8, 9 }
    };

    pair<int, int> pos(1,1);

    ifstream in("Bathroom_Security_Input.txt");
    if(!in)
    {
        cerr << "Cannot find file." << endl;
        return;
    }

    string Line;
    while (in)
    {
        getline(in, Line);
        
        if(Line.length() > 0)
        {
            for (int i = 0; i < Line.length(); ++i)
            {
                const char c = Line[i];

                switch (c)
                {
                    case 'U': { advance(pos, 0, -1); break; }
                    case 'D': { advance(pos, 0, 1); break; }
                    case 'R': { advance(pos, 1, 0); break; }
                    case 'L': { advance(pos, -1, 0); break; }
                }
            }

            cout << Keypad[pos.second][pos.first];
        }
    }


    /*
    vector<string> Code = {
        "ULL",
        "RRDDD",
        "LURDL",
        "UUUUD"
    };


    for (int l = 0; l < Code.size(); ++l)
    {
        const string& Line = Code[l];

        for (int i = 0; i < Line.length(); ++i)
        {
            const char c = Line[i];

            switch (c)
            {
                case 'U': { advance(pos, 0, -1); break; }
                case 'D': { advance(pos, 0, 1); break; }
                case 'R': { advance(pos, 1, 0); break; }
                case 'L': { advance(pos, -1, 0); break; }
            }
        }

        cout << Keypad[pos.second][pos.first];
    }
    */
    
    cout << endl;
}

void Bathroom_Security__Part_2()
{
    vector<vector<char>> keypad = {
        { '0', '0', '1', '0','0' }, 
        { '0', '2', '3', '4','0' },
        { '5', '6', '7', '8','9' },
        { '0', 'A', 'B', 'C','0' },
        { '0', '0', 'D', '0','0' }
    };

    // Start is at '5'
    pair<int, int> pos(0,2);

    ifstream in("Bathroom_Security_Input.txt");
    if(!in)
    {
        cerr << "Cannot find file." << endl;
        return;
    }

    string Line;
    while (in)
    {
        getline(in, Line);
        
        if(Line.length() > 0)
        {
            for (int i = 0; i < Line.length(); ++i)
            {
                const char c = Line[i];

                switch (c)
                {
                    case 'U': { advance(keypad, pos,  0, -1); break; }
                    case 'D': { advance(keypad, pos,  0,  1); break; }
                    case 'R': { advance(keypad, pos,  1,  0); break; }
                    case 'L': { advance(keypad, pos, -1,  0); break; }
                }
            }

            cout << keypad[pos.second][pos.first];
        }
    }


    //vector<string> Code = {
    //    "ULL",
    //    "RRDDD",
    //    "LURDL",
    //    "UUUUD"
    //};


    //for (int l = 0; l < Code.size(); ++l)
    //{
    //    const string& Line = Code[l];

    //    for (int i = 0; i < Line.length(); ++i)
    //    {
    //        const char c = Line[i];

    //        switch (c)
    //        {
    //            case 'U': { advance(keypad, pos,  0, -1); break; }
    //            case 'D': { advance(keypad, pos,  0,  1); break; }
    //            case 'R': { advance(keypad, pos,  1,  0); break; }
    //            case 'L': { advance(keypad, pos, -1,  0); break; }
    //        }
    //    }

    //    cout << keypad[pos.second][pos.first];
    //}
    
    cout << endl;
}

void Squares_With_Three_Sides()
{
    ifstream in("Triangles_Input.txt");
    if(!in)
    {
        cerr << "Cannot find file." << endl;
        return;
    }

    int Counter = 0;

    string Line;
    while (in)
    {
        getline(in, Line);

        if(Line.length() > 0)
        {
            int a[3];

            istringstream is(Line);
            for(int i = 0; i < 3; ++i)
            {
                is >> a[i];
            }

            sort(&a[0], &a[3]);

            // the triangle inequality states that for any triangle, the sum of the lengths of any two sides must be greater than or equal to the length of the remaining side
            
            // according to wikipedia >= is possible as well. In this coding challenge it's not.
            if((a[0] + a[1]) > a[2])
            {
                Counter++;
            }
            else
            {
                int bla = 99;
            }
        }
    }


    cout << Counter << endl;




    //string triangle = "99 10 25";
    //int a[3];

    //istringstream is(triangle);
    //for(int i = 0; i < 3; ++i)
    //{
    //    is >> a[i];
    //}

    //sort(&a[0], &a[3]);


    //// the triangle inequality states that for any triangle, the sum of the lengths of any two sides must be greater than or equal to the length of the remaining side
    //if((a[0] + a[1]) >= a[2])
    //{
    //    cout << "valid" << endl;
    //}
}

///
/// Instead of defining a triangle by a line in the input file, a triangle is made up by three values of each column.
/// E.g
/// 
/// 123 123 123
/// 456 456 456
/// 789 789 789
/// 
/// These three lines define three triangle (123, 456, 789)
/// 
void Squares_With_Three_Sides__Part_2()
{
    ifstream in("Triangles_Input.txt");
    if(!in)
    {
        cerr << "Cannot find file." << endl;
        return;
    }

    vector<vector<int>> numbers;    
    
    int Triangle_Counter = 0;
    int Not_Triangle_Counter = 0;

    string Line;
    while (in)
    {
        getline(in, Line);

        if(Line.length() > 0)
        {
            istringstream is(Line);
            int a[3];
            is >> a[0];
            is >> a[1];
            is >> a[2];

            numbers.push_back(vector<int>());
            numbers.back().push_back(a[0]);
            numbers.back().push_back(a[1]);
            numbers.back().push_back(a[2]);

            if((numbers.size() % 3) == 0)
            {
                vector<vector<int>> triangles;
            
                for(int c = 0; c < 3; c++)
                {
                    a[0] = numbers[0][c];
                    a[1] = numbers[1][c];
                    a[2] = numbers[2][c];

                    // !!! one past back !!!
                    sort(&a[0], &a[3]);

                    if((a[0] + a[1]) > a[2])
                    {
                        Triangle_Counter++;
                    }
                    else
                    {
                        Not_Triangle_Counter++;
                    }
                }
        
                numbers.clear();
            }
        }
        
      

        //if(Line.length() > 0)
        //{
        //    int a[3];

        //    istringstream is(Line);
        //    for(int i = 0; i < 3; ++i)
        //    {
        //        is >> a[i];
        //    }

        //    sort(&a[0], &a[3]);

        //    if((a[0] + a[1]) > a[2])
        //    {
        //        Triangle_Counter++;
        //    }
        //}
    }


    cout << Triangle_Counter << endl;
    cout << Not_Triangle_Counter << endl;
}

void Security_Through_Obscurity()
{
    ifstream in("Rooms.txt");
    if(!in)
    {
        cerr << "Cannot find file." << endl;
        return;
    }
   
    {
        //string Line = "not-a-real-room-404[oarel]";
        string Line = "a-b-c-d-e-f-g-h-987[abcde]";

        string name = Line.substr(0, Line.find_last_of('-'));
        string sector_id = Line.substr(Line.find_last_of('-') + 1, Line.find_last_of('[') - Line.find_last_of('-') - 1);
        string checksum = Line.substr(Line.find('[') + 1, Line.find_last_of(']') - Line.find('[') - 1);

        assert(name.length() > 0);
        assert(sector_id.length() > 0);
        assert(checksum.length() > 0);
        assert(atoi(sector_id.c_str()) > 0);
    
        // check if checksum is correct
        map<char, int> histogram;
        
        for(auto c : name)
        {
            if(c != '-')
            {
                histogram[c]++;
            }
        }

        vector<pair<char,int>> generated_checksum(histogram.size());
        copy(histogram.begin(), histogram.end(), generated_checksum.begin());

        // sort by count
        sort(generated_checksum.begin()
            , generated_checksum.end()
            , [](const pair<char,int>& a, const pair<char, int>& b) -> bool { return a.second > b.second; });

        // sort letter alphabetically when count is equal
        int max_count = generated_checksum.front().second;

        for(int c = max_count; c > 0; --c)
        {
            auto it = find_if(generated_checksum.begin()
                , generated_checksum.end()
                , [c](const pair<char,int>& p) { return p.second == c; });

            decltype(it) end = it + 1;

            while(end < generated_checksum.end())
            {
                if(end->second != c)
                {
                    break;
                }

                end++;
            }

            if(distance(it,end) > 1)
            {
                sort(it, end, [](const pair<char,int>& a, const pair<char, int>& b) -> bool { return a.first < b.first; });
            }
        }
    }



    string Line;
    while (in)
    {
        getline(in, Line);

        if(Line.length() > 0)
        {
            string code = Line.substr(0, Line.find('['));
            string checksum = Line.substr(Line.find('['), Line.find_last_of(']'));

        }
    }
}



int main()
{
    //No_Time_For_A_Taxi_Cab();
    //No_Time_For_A_Taxi_Cab__Part_2();

    //Bathroom_Security();
    //Bathroom_Security__Part_2();

    //Squares_With_Three_Sides();
    //Squares_With_Three_Sides__Part_2();

    Security_Through_Obscurity();

    return 0;
}

