// AdventOfCode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cassert>

#include <fstream>
#include <iostream>
#include <string>
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

    ifstream in("input.txt");
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

    ifstream in("input.txt");
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


int main()
{
    //No_Time_For_A_Taxi_Cab();
    //No_Time_For_A_Taxi_Cab__Part_2();

    //Bathroom_Security();
    Bathroom_Security__Part_2();

    return 0;
}

