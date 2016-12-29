
// http://adventofcode.com/

#include "stdafx.h"

#include <cassert>
#include <cmath>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <regex>
#include <string>
#include <sstream>
#include <vector>

// see https://www.nayuki.io/page/fast-md5-hash-implementation-in-x86-assembly
extern "C" void md5_compress(uint32_t state[4], const uint8_t block[64]);
extern "C" void md5_hash(const uint8_t *message, size_t len, uint32_t hash[4]);

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


string process_room_code(const string& name )
{
        // count each letter
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

        // sort by count descending and if count is equal sort by letter ascending
        sort(generated_checksum.begin()
            , generated_checksum.end()
            , [](const pair<char,int>& a, const pair<char, int>& b) -> bool 
            { 
                if(a.second == b.second)
                {
                    return a.first < b.first;
                }

                return a.second > b.second; 
            });

        string checksum = "";
        for(int i = 0; i < 5; ++i)
        {
            checksum += generated_checksum[i].first;
        }

        return checksum;
}

void Security_Through_Obscurity()
{
    //{
    //    vector<string> test_data = 
    //    {
    //        "aaaaa-bbb-z-y-x-123[abxyz]", 
    //        "a-b-c-d-e-f-g-h-987[abcde]", 
    //        "not-a-real-room-404[oarel]",
    //        "totally-real-room-200[decoy]"
    //    };
    //    
    //    for(auto& s : test_data)
    //    {
    //        string name = s.substr(0, s.find_last_of('-'));
    //        string sector_id = s.substr(s.find_last_of('-') + 1, s.find_last_of('[') - s.find_last_of('-') - 1);
    //        string checksum = s.substr(s.find('[') + 1, s.find_last_of(']') - s.find('[') - 1);

    //        assert(name.length() > 0);
    //        assert(sector_id.length() > 0);
    //        assert(checksum.length() > 0);
    //        assert(atoi(sector_id.c_str()) > 0);

    //        auto generated_checksum = process_room_code(name);

    //        if(generated_checksum == checksum)
    //        {
    //            cout << s << " is a room" << endl;
    //        }
    //        else
    //        {
    //            cout << s << " is not a room" << endl;
    //        }
    //    }
    //}


    int sum_sector_id = 0;

    ifstream in("Rooms.txt");
    if(!in)
    {
        cerr << "Cannot find file." << endl;
        return;
    }

    string s;
    while (in)
    {
        getline(in, s);

        if(s.length() > 0)
        {
            string name = s.substr(0, s.find_last_of('-'));
            string sector_id = s.substr(s.find_last_of('-') + 1, s.find_last_of('[') - s.find_last_of('-') - 1);
            string checksum = s.substr(s.find('[') + 1, s.find_last_of(']') - s.find('[') - 1);

            assert(name.length() > 0);
            assert(sector_id.length() > 0);
            assert(checksum.length() > 0);
            assert(atoi(sector_id.c_str()) > 0);

            auto generated_checksum = process_room_code(name);

            if(generated_checksum == checksum)
            {
                sum_sector_id += atoi(sector_id.c_str());
            }
        }
    }

    cout << sum_sector_id << endl;
}

void Security_Through_Obscurity__Part_2()
{
    //{
    //    string test = "qzmt-zixmtkozy-ivhz-343";

    //    string name = test.substr(0, test.find_last_of('-'));
    //    string sector_id = test.substr(test.find_last_of('-') + 1, string::npos);

    //    int num_shifts = atoi(sector_id.c_str());
    //    char c = 'q';

    //    for( auto& c : name)
    //    {
    //        if( c == '-' ) 
    //        {
    //            c = ' ';
    //            continue;
    //        }
    //    
    //        for (int i = 0; i < num_shifts; i++)
    //        {
    //            c++;
    //            if(c > 'z') { c = 'a'; }
    //        }
    //    }
    //}

    ifstream in("Rooms.txt");
    if(!in)
    {
        cerr << "Cannot find file." << endl;
        return;
    }

    string s;
    while (in)
    {
        getline(in, s);

        if(s.length() > 0)
        {
            string name = s.substr(0, s.find_last_of('-'));
            string sector_id = s.substr(s.find_last_of('-') + 1, s.find_last_of('[') - s.find_last_of('-') - 1);
            string checksum = s.substr(s.find('[') + 1, s.find_last_of(']') - s.find('[') - 1);

            assert(name.length() > 0);
            assert(sector_id.length() > 0);
            assert(checksum.length() > 0);
            assert(atoi(sector_id.c_str()) > 0);

            auto generated_checksum = process_room_code(name);

            if(generated_checksum == checksum)
            {
                int num_shifts = atoi(sector_id.c_str());

                for( auto& c : name)
                {
                    if( c == '-' ) 
                    {
                        c = ' ';
                        continue;
                    }
                    
                    for (int i = 0; i < num_shifts; i++)
                    {
                        c++;
                        if(c > 'z') { c = 'a'; }
                    }
                }

                if(name.find("north") != string::npos)
                {
                    cout << name << endl;
                    cout << sector_id << endl;
                }
            }
        }
    }
}

uint32_t ChangeEndianness(uint32_t value)
{
    uint32_t result = 0;
    result |= (value & 0x000000FF) << 24;
    result |= (value & 0x0000FF00) << 8;
    result |= (value & 0x00FF0000) >> 8;
    result |= (value & 0xFF000000) >> 24;
    return result;
}

void Hash_Password()
{
    //uint32_t hash[4];
    //string test = "abc3231929";
    //md5_hash((uint8_t*) test.c_str(), strlen(test.c_str()), hash);
    //auto _0 = ChangeEndianness(hash[0]);

    //uint32_t a = 0x00000FFF;
    //if(_0 <= a)
    //{
    //    // bingo
    //    int iiii = 99;
    //}


    //uint32_t hash[4];
    //vector<uint8_t> bytes(10);
    //bytes[0] = 'a';
    //bytes[1] = 'b';
    //bytes[2] = 'c';
    ////   90015098
    //// 0x90015098
    ////uint32_t hash[4];
    //md5_hash(&bytes[0], 3, hash);
    //uint32_t _0 = ChangeEndianness(hash[0]);

    // test with http://www.miraclesalad.com/webtools/md5.php

    uint32_t hash[4];

    string door_id = "reyedfim";

    auto s = door_id.length();

    vector<uint8_t> bytes(100);

    for(int c = 0; c < door_id.length(); ++c)
    {
        bytes[c] = door_id[c];
    }

    size_t size = door_id.length();

    uint32_t upper_boundary = 0x00000FFF;

    vector<uint32_t> pw_pieces;

    for(uint32_t i = 0; i < UINT32_MAX; ++i)
    {
        uint32_t i_copy = i;

        int offset = (i > 0) ? (int)(log10(i) + 1.0) : 1;
        for(int j = offset; j > 0; --j)
        {
            // add i as char
            bytes[size + j - 1] = (i_copy % 10) + 48;
            i_copy /= 10;
        }

        md5_hash(&bytes[0], size + offset, hash);
        uint32_t _0 = ChangeEndianness(hash[0]);

        if(_0 <= upper_boundary)
        {
            pw_pieces.push_back(_0);

            if(pw_pieces.size() == 8)
            {
                break;
            }
        }

    }

    for(auto p : pw_pieces)
    {
        cout << std::hex << (p / 16 ) / 16;
    }

    cout << endl;
}

void Hash_Password__Part_2()
{
    // test with http://www.miraclesalad.com/webtools/md5.php

    uint32_t hash[4];

    string door_id = "reyedfim";
    //string door_id = "abc";

    auto s = door_id.length();

    vector<uint8_t> bytes(100);

    for(int c = 0; c < door_id.length(); ++c)
    {
        bytes[c] = door_id[c];
    }

    size_t size = door_id.length();

    uint32_t upper_boundary = 0x00000FFF;

    string password(8, '_');

    for(uint32_t i = 0; i < UINT32_MAX; ++i)
    {
        uint32_t i_copy = i;

        int offset = (i > 0) ? log10(i) + 1.0 : 1;
        for(int j = offset; j > 0; --j)
        {
            // add i as char
            bytes[size + j - 1] = (i_copy % 10) + 48;
            i_copy /= 10;
        }

        md5_hash(&bytes[0], size + offset, hash);
        uint32_t _0 = ChangeEndianness(hash[0]);

        if(_0 <= upper_boundary)
        {
            stringstream ss;
            ss << setfill('0') << setw(sizeof(uint32_t) * 2) << hex << _0;
            string hex_number = ss.str();

            // sixth character - must be value between 0 and 7
            uint8_t pos = hex_number[5] - '0';
            char value = hex_number[6];

            if(pos >= 0 && pos < 8)
            {
                if(password[pos] == '_')
                {
                    // seventh character - can be any hex character
                    password[pos] = value;

                    cout << password << endl;

                    if(password.find('_') == string::npos)
                    {
                        return;
                    }
                }
            }
        }
    }
}

void Signal_And_Noise()
{
/*
    vector<string> test = {
        "eedadn",
        "drvtee",
        "eandsr",
        "raavrd",
        "atevrs",
        "tsrnev",
        "sdttsa",
        "rasrtv",
        "nssdts",
        "ntnada",
        "svetve",
        "tesnvt",
        "vntsnd",
        "vrdear",
        "dvrsen",
        "enarar"
    };

    int num_chars = 6;

    vector<map<char, int>> common_char(num_chars);

    for(auto& s : test)
    {
        for(int c = 0; c < s.length(); ++c)
        {
            assert(c<num_chars);

            common_char[c][s[c]]++;
        }
    }

    for(auto& m : common_char)
    {
        vector<pair<char,int>> d(m.size());

        copy(m.begin(), m.end(), d.begin());
        sort(d.begin(), d.end()
            , [](const pair<char,int>& a, const pair<char,int>& b)
            {
                return a.second > b.second;
            });

        auto max_count = d.front().second;
        auto max_letter = d.front().first;
        assert(d[1].second < max_count);

        cout << max_letter;
    }

    cout << endl;
*/

    int num_columns = 8;
    vector<map<char, int>> characters_by_column(num_columns);

    ifstream in("Signal_and_Noise.txt");
    if(!in)
    {
        cerr << "Cannot find file." << endl;
        return;
    }

    int line_counter = 0;
    string s;
    while (in)
    {
        getline(in, s);

        if(s.length() > 0)
        {
            line_counter++;
            assert(s.length() == num_columns);

            for(int c = 0; c < s.length(); ++c)
            {
                characters_by_column[c][s[c]]++;
            }
        }
    }

    for(auto& m : characters_by_column)
    {
        vector<pair<char,int>> d(m.size());

        copy(m.begin(), m.end(), d.begin());
        sort(d.begin(), d.end()
            , [](const pair<char,int>& a, const pair<char,int>& b)
            {
                return a.second > b.second;
            });

        auto max_count = d.front().second;
        auto max_letter = d.front().first;
        assert(d[1].second < max_count);

        cout << max_letter;
    }

    cout << endl;

    cout << "processed " << line_counter << " lines" << endl;
}

void Signal_And_Noise__Part_2()
{
/*
    vector<string> test = {
        "eedadn",
        "drvtee",
        "eandsr",
        "raavrd",
        "atevrs",
        "tsrnev",
        "sdttsa",
        "rasrtv",
        "nssdts",
        "ntnada",
        "svetve",
        "tesnvt",
        "vntsnd",
        "vrdear",
        "dvrsen",
        "enarar"
    };

    int num_chars = 6;

    vector<map<char, int>> common_char(num_chars);

    for(auto& s : test)
    {
        for(int c = 0; c < s.length(); ++c)
        {
            assert(c<num_chars);

            common_char[c][s[c]]++;
        }
    }

    for(auto& m : common_char)
    {
        vector<pair<char,int>> d(m.size());

        copy(m.begin(), m.end(), d.begin());
        sort(d.begin(), d.end()
            , [](const pair<char,int>& a, const pair<char,int>& b)
            {
                return a.second < b.second;
            });

        auto min_count = d.front().second;
        auto min_letter = d.front().first;
        assert(d[1].second > min_count);

        cout << min_letter;
    }

    cout << endl;
*/

    int num_columns = 8;
    vector<map<char, int>> characters_by_column(num_columns);

    ifstream in("Signal_and_Noise.txt");
    if(!in)
    {
        cerr << "Cannot find file." << endl;
        return;
    }

    int line_counter = 0;
    string s;
    while (in)
    {
        getline(in, s);

        if(s.length() > 0)
        {
            line_counter++;
            assert(s.length() == num_columns);

            for(int c = 0; c < s.length(); ++c)
            {
                characters_by_column[c][s[c]]++;
            }
        }
    }

    for(auto& m : characters_by_column)
    {
        vector<pair<char,int>> d(m.size());

        copy(m.begin(), m.end(), d.begin());
        sort(d.begin(), d.end()
            , [](const pair<char,int>& a, const pair<char,int>& b)
            {
                return a.second < b.second;
            });

        auto min_count = d.front().second;
        auto min_letter = d.front().first;
        assert(d[1].second > min_count);

        cout << min_letter;
    }

    cout << endl;

    cout << "processed " << line_counter << " lines" << endl;
}

void IP_Protocol_7()
{
    /*
    vector<string> test = {
        "abba[mnop]qrst",
        "abcd[bddb]xyyx",
        "aaaa[qwer]tyui",
        "ioxxoj[asdfgh]zxcvbn"
    };

    for(auto& s : test)
    {
        // outside []
        vector<string> outside;
        
        // inside []
        vector<string> inside;
        
        bool pos_outside = true;
        bool new_string = true;


        for(auto c : s)
        {

            // first check if any state changing

            if(c == '[')
            {
                pos_outside = false;
                new_string = true;
                
                continue;
            }

            if(c == ']')
            {
                pos_outside = true;
                new_string = true;
                
                continue;
            }

            // assign characters

            if(pos_outside)
            {
                if(new_string)
                {
                    outside.push_back("");
                    new_string = false;
                }

                outside.back() += c;
            }
            else
            {
                if(new_string)
                {
                    inside.push_back("");
                    new_string = false;
                }

                inside.back() += c;
            }
        }
    }
    */

    ifstream in("Day7.txt");
    if(!in)
    {
        cerr << "Cannot find file." << endl;
        return;
    }

    int Counter = 0;

    int line_counter = 0;
    string s;
    while (in)
    {
        getline(in, s);

        if(s.length() > 0)
        {
            // contains current IP address piece
            string p;
        
            bool outside = true;
            bool new_piece = true;
            
            
            bool outside_good = false;
            bool inside_good = true;

            for(auto c : s)
            {
                // first check if any state changing

                if(c == '[')
                {
                    outside = false;
                    new_piece = true;
                
                    continue;
                }

                if(c == ']')
                {
                    outside = true;
                    new_piece = true;
                
                    continue;
                }

                // assign characters


                if(outside && outside_good == false)
                {
                    if(new_piece)
                    {
                        p.clear();
                        new_piece = false;
                    }

                    p += c;

                    if(p.length() >= 4)
                    {
                        string w = p.substr(p.length() - 4, 4);

                        if(w[0] == w[3] && w[1] == w[2] && w[0] != w[1])
                        {
                            outside_good = true;
                        }
                    }
                }
                else if(outside == false && inside_good == true)
                {
                    if(new_piece)
                    {
                        p.clear();
                        new_piece = false;
                    }

                    p += c;

                    if(p.length() >= 4)
                    {
                        string w = p.substr(p.length() - 4, 4);

                        if(w[0] == w[3] && w[1] == w[2] && w[0] != w[1])
                        {
                            inside_good = false;
                        }
                    }
                }
            }
        
            if(outside_good && inside_good)
            {
                cout << ++Counter << ": " << s << endl;
            }
        } 
    }
}

void IP_Protocol_7__Part_2()
{
/*
    vector<string> test = {
        "aba[bab]xyz",
        "xyx[xyx]xyx",
        "aaa[kek]eke",
        "zazbz[bzb]cdb"
    };

    for(auto& s : test)
    {
        vector<string> ABAs;
        vector<string> BABs;

        // contains current IP address piece
        string p;
        
        bool outside = true;
        bool new_piece = true;
            
        for(auto c : s)
        {
            // first check if any state changing

            if(c == '[')
            {
                outside = false;
                new_piece = true;
                
                continue;
            }

            if(c == ']')
            {
                outside = true;
                new_piece = true;
                
                continue;
            }

            // assign characters

            if(outside)
            {
                if(new_piece)
                {
                    p.clear();
                    new_piece = false;
                }

                p += c;

                if(p.length() >= 3)
                {
                    char a = p[p.length() - 3];
                    char b = p[p.length() - 2];
                    char c = p[p.length() - 1];

                    if(a == c && a != b)
                    {
                        // put allocator in block (aka BAB) order to matching is easier

                        stringstream ss;
                        ss << b << a << b;
                        ABAs.push_back(ss.str());
                    }
                }
            }
            else
            {
                if(new_piece)
                {
                    p.clear();
                    new_piece = false;
                }

                p += c;

                if(p.length() >= 3)
                {
                    char a = p[p.length() - 3];
                    char b = p[p.length() - 2];
                    char c = p[p.length() - 1];

                    if(a == c && a != b)
                    {
                        BABs.push_back(p.substr(p.length() - 3, 3));
                    }
                }
            }
        }
    
        // check for match
        vector<string> Union(ABAs.size() + BABs.size());

        sort(ABAs.begin(), ABAs.end());
        sort(BABs.begin(), BABs.end());
        auto it = set_union(ABAs.begin(), ABAs.end(), BABs.begin(), BABs.end(), Union.begin());

        if(it == Union.end())
        {
            cout << "Not a match: " << s << endl;
        }
        else
        {
            cout << "A match: " << s << endl;
        }
    }

*/

    ifstream in("Day7.txt");
    if(!in)
    {
        cerr << "Cannot find file." << endl;
        return;
    }



    int Counter = 0;

    int line_counter = 0;
    string s;
    while (in)
    {
        getline(in, s);

        if(s.length() > 0)
        {
            vector<string> ABAs;
            vector<string> BABs;

            // contains current IP address piece
            string p;
        
            bool outside = true;
            bool new_piece = true;
            
            for(auto c : s)
            {
                // first check if any state changing

                if(c == '[')
                {
                    outside = false;
                    new_piece = true;
                
                    continue;
                }

                if(c == ']')
                {
                    outside = true;
                    new_piece = true;
                
                    continue;
                }

                // assign characters

                if(outside)
                {
                    if(new_piece)
                    {
                        p.clear();
                        new_piece = false;
                    }

                    p += c;

                    if(p.length() >= 3)
                    {
                        char a = p[p.length() - 3];
                        char b = p[p.length() - 2];
                        char c = p[p.length() - 1];

                        if(a == c && a != b)
                        {
                            // put allocator in block (aka BAB) order to matching is easier

                            stringstream ss;
                            ss << b << a << b;
                            ABAs.push_back(ss.str());
                        }
                    }
                }
                else
                {
                    if(new_piece)
                    {
                        p.clear();
                        new_piece = false;
                    }

                    p += c;

                    if(p.length() >= 3)
                    {
                        char a = p[p.length() - 3];
                        char b = p[p.length() - 2];
                        char c = p[p.length() - 1];

                        if(a == c && a != b)
                        {
                            BABs.push_back(p.substr(p.length() - 3, 3));
                        }
                    }
                }
            }
    
            // check for match
            vector<string> intersection(ABAs.size() + BABs.size());

            sort(ABAs.begin(), ABAs.end());
            sort(BABs.begin(), BABs.end());
            auto it = set_intersection(ABAs.begin(), ABAs.end(), BABs.begin(), BABs.end(), intersection.begin());

            intersection.resize(it - intersection.begin());

            if(intersection.size() > 0)
            {
                cout << ++Counter << ": " << s << endl;
            }
        } 
    }
}

void draw(int** screen, const int num_rows, const int num_columns, const vector<string>& instructions)
{
    for(auto& i : instructions)
    {
        if(i.find("rect") != string::npos)
        {
            regex r("rect\\s*(\\d+)\\s*x\\s*(\\d+)");
            smatch m;

            if(regex_match(i, m, r))
            {
                int width = atoi(m[1].str().c_str());
                int height = atoi(m[2].str().c_str());

                assert(width > 0);
                assert(height > 0);

                for(int y = 0; y < height; ++y)
                {
                    for(int x = 0; x < width; ++x)
                    {
                        screen[y][x] = 1;
                    }
                }

            }
        }
        else if(i.find("rotate column") != string::npos)
        {
            regex r("rotate column\\s*x=(\\d+)\\s*by\\s*(\\d+)");
            smatch m;

            if(regex_match(i, m, r))
            {
                int column = atoi(m[1].str().c_str());
                int value = atoi(m[2].str().c_str());

                assert(column >= 0);
                assert(column < num_columns);
                
                assert(value > 0);

                int inc = value % num_rows;

                // make a copy of col as data source
                vector<int> c(num_rows);
                for(int y = 0; y < num_rows; ++y)
                {
                    c[y] = screen[y][column];
                }

                for(int y = 0; y < num_rows; ++y)
                {
                    int new_y = ((y + inc) < num_rows) ? y + inc : y + inc - num_rows;
                    screen[new_y][column] = c[y];
                }
            }
        }
        else if(i.find("rotate row") != string::npos)
        {
            regex r("rotate row\\s*y=(\\d+)\\s*by\\s*(\\d+)");
            smatch m;

            if(regex_match(i, m, r))
            {
                int row = atoi(m[1].str().c_str());
                int value = atoi(m[2].str().c_str());

                assert(row >= 0);
                assert(row < num_rows);

                assert(value > 0);

                int inc = value % num_columns;

                // make a copy of row as data source
                vector<int> r(num_columns);
                for(int x = 0; x < num_columns; ++x)
                {
                    r[x] = screen[row][x];
                }

                for(int x = 0; x < num_columns; ++x)
                {
                    int new_x = ((x + inc) < num_columns) ? x + inc : x + inc - num_columns;
                    screen[row][new_x] = r[x];
                }
            }
        }
        else
        {
            cerr << "Cannot understand instruction: " << i << endl;
        }
    }
}

void Two_Factor_Authentication()
{
/*
    const int num_rows = 3;
    const int num_columns = 7;
    
    int** screen = new int*[num_rows];

    for(int y = 0; y < num_rows; ++y)
    {
        screen[y] = new int[num_columns];
    }


    for(int y = 0; y < num_rows; ++y)
    {
        for(int x = 0; x < num_columns; ++x)
        {
            screen[y][x] = 0;
        }
    }


    vector<string> instructions 
    {
        "rect 3x2",
        "rotate column x=1 by 1",
        "rotate row y=0 by 4",
        "rotate column x=1 by 1"
    };

    draw(screen, num_rows, num_columns, instructions);

    assert(screen[0][0]== 0);
    assert(screen[0][1]== 1);
    assert(screen[0][2]== 0);
    assert(screen[0][3]== 0);
    assert(screen[0][4]== 1);
    assert(screen[0][5]== 0);
    assert(screen[0][6]== 1);

    assert(screen[1][0]== 1);
    assert(screen[1][1]== 0);
    assert(screen[1][2]== 1);
    assert(screen[1][3]== 0);
    assert(screen[1][4]== 0);
    assert(screen[1][5]== 0);
    assert(screen[1][6]== 0);

    assert(screen[2][0]== 0);
    assert(screen[2][1]== 1);
    assert(screen[2][2]== 0);
    assert(screen[2][3]== 0);
    assert(screen[2][4]== 0);
    assert(screen[2][5]== 0);
    assert(screen[2][6]== 0);
*/

    ifstream in("Day8.txt");
    if(!in)
    {
        cerr << "Cannot find file." << endl;
        return;
    }


    vector<string> instructions;

    string s;
    while (in)
    {
        getline(in, s);

        if(s.length() > 0)
        {
            instructions.push_back(s);
        }
    }

    const int num_rows = 6;
    const int num_columns = 50;
    
    int** screen = new int*[num_rows];

    for(int y = 0; y < num_rows; ++y)
    {
        screen[y] = new int[num_columns];
    }


    for(int y = 0; y < num_rows; ++y)
    {
        for(int x = 0; x < num_columns; ++x)
        {
            screen[y][x] = 0;
        }
    }

    draw(screen, num_rows, num_columns, instructions);

    int on_pixels = 0;
    for(int y = 0; y < num_rows; ++y)
    {
        for(int x = 0; x < num_columns; ++x)
        {
            if(screen[y][x] == 1)
            {
                ++on_pixels;
            }
        }
    }

    cout << on_pixels << endl;
}

void Two_Factor_Authentication__Part_2()
{
    ifstream in("Day8.txt");
    if(!in)
    {
        cerr << "Cannot find file." << endl;
        return;
    }


    vector<string> instructions;

    string s;
    while (in)
    {
        getline(in, s);

        if(s.length() > 0)
        {
            instructions.push_back(s);
        }
    }

    const int num_rows = 6;
    const int num_columns = 50;
    
    int** screen = new int*[num_rows];

    for(int y = 0; y < num_rows; ++y)
    {
        screen[y] = new int[num_columns];
    }


    for(int y = 0; y < num_rows; ++y)
    {
        for(int x = 0; x < num_columns; ++x)
        {
            screen[y][x] = 0;
        }
    }

    draw(screen, num_rows, num_columns, instructions);



    int on_pixels = 0;
    for(int y = 0; y < num_rows; ++y)
    {
        for(int x = 0; x < num_columns; ++x)
        {
            if((x % 5) == 0)
            {
                cout << "  ";
            }
            
            cout << ((screen[y][x] == 0) ? '.' : '8');
        }
    
        cout << endl;
    }

}

void Explosives_In_Cyberspace()
{
    //vector<string> test = {
    //    "ADVENT",
    //    "A(1x5)BC",
    //    "(3x3)XYZ",
    //    "(6x1)(1x3)A",
    //    "X(8x2)(3x3)ABCY"
    //};


    //for(const auto& s : test)
    //{
    //    string marker = "";
    //    string output = "";

    //    // length of data section
    //    int n = 0;
    //    
    //    // how often to repeat
    //    int m = 0;

    //    for(int i = 0; i < s.length(); ++i)
    //    {
    //        char c = s[i];
    //        
    //        if(marker == "" && c == '(')
    //        {
    //            // read marker
    //            for(++i;i < s.length();++i)
    //            {
    //                c = s[i];

    //                if(c == ')')
    //                {
    //                    break;
    //                }

    //                marker += c;
    //            }
    //        
    //            string n_value = marker.substr(0, marker.find('x'));
    //            string m_value = marker.substr(marker.find('x') + 1);

    //            n = atoi(n_value.c_str());
    //            m = atoi(m_value.c_str());

    //            assert(n > 0);
    //            assert(m > 0);

    //            continue;
    //        }

    //        if(marker == "")
    //        {
    //            output += c;
    //        }
    //        else
    //        {
    //            for(int r = 0; r < m; ++r)
    //            {
    //                for(int j = i; j < n + i; ++j)
    //                {
    //                    assert(j < s.length());
    //                    
    //                    c = s[j];
    //                    
    //                    output += c; 
    //                }
    //            }

    //            i += n - 1;

    //            marker.clear();
    //            n = 0;
    //            m = 0;
    //        }
    //    }
    //}

    ifstream in("Day9.txt");
    if(!in)
    {
        cerr << "Cannot find file." << endl;
        return;
    }

    string s;
    while (in)
    {
        getline(in, s);

        if(s.length() > 0)
        {
            string marker = "";
            string output = "";

            // length of data section
            int n = 0;
        
            // how often to repeat
            int m = 0;

            for(int i = 0; i < s.length(); ++i)
            {
                char c = s[i];
            
                if(marker == "" && c == '(')
                {
                    // read marker
                    for(++i;i < s.length();++i)
                    {
                        c = s[i];

                        if(c == ')')
                        {
                            break;
                        }

                        marker += c;
                    }
            
                    string n_value = marker.substr(0, marker.find('x'));
                    string m_value = marker.substr(marker.find('x') + 1);

                    n = atoi(n_value.c_str());
                    m = atoi(m_value.c_str());

                    assert(n > 0);
                    assert(m > 0);

                    continue;
                }

                if(marker == "")
                {
                    output += c;
                }
                else
                {
                    for(int r = 0; r < m; ++r)
                    {
                        for(int j = i; j < n + i; ++j)
                        {
                            assert(j < s.length());
                        
                            c = s[j];
                        
                            output += c; 
                        }
                    }

                    i += n - 1;

                    marker.clear();
                    n = 0;
                    m = 0;
                }
            }
        
            assert(output.find(' ') == string::npos);
            cout << output.length() << endl;

        }

    }
}


string extract_first_marker(const string& s, int& n, int& m)
{
    assert(s[0] == '(');
    string n_value = s.substr(1, s.find('x'));
    string m_value = s.substr(s.find('x') + 1, s.find(')'));

    n = atoi(n_value.c_str());
    m = atoi(m_value.c_str());

    assert(n > 0);
    assert(m > 0);

    return s.substr(s.find(')') + 1);
}

void print(const uint64_t& c)
{
    if(c > 0 && (c % 1000000) == 0)
    {
        cout << c << endl;
    }
}

uint64_t function_calls = 0;

void process(const string& s, uint64_t& length)
{
    ++function_calls;

    // 
    if(s.find('(') == string::npos)
    {
        length += s.length();
        
        print(length);
        return;
    }

    string prefix = s.substr(0,s.find('('));
    process(prefix, length);
    
    // decompress marker
    string compressed = s.substr(s.find('('));
    int n = 0;
    int m = 0;
    string section = extract_first_marker(compressed, n, m);
    
    for(int i = 0; i < m; ++i)
    {
        string a = section.substr(0, n);
        process(a, length);
    }
    
    string b = section.substr(n);
    process(b, length);
}


void Explosives_In_Cyberspace__Part_2()
{
    /*
    vector<string> test = {
        "(3x3)XYZ",
        "X(8x2)(3x3)ABCY",
        "(27x12)(20x12)(13x14)(7x10)(1x12)A",
        "(25x3)(3x3)ABC(2x3)XY(5x2)PQRSTX(18x9)(3x2)TWO(5x7)SEVEN"
    };

    for(const auto& s : test)
    {
        uint64_t length = 0;
        process(s, length);
    
        cout << s << "  ---  " << length << endl;
    }
    */

    ifstream in("Day9.txt");
    if(!in)
    {
        cerr << "Cannot find file." << endl;
        return;
    }

    string s;
    while (in)
    {
        getline(in, s);

        if(s.length() > 0)
        {
            uint64_t length = 0;
            process(s, length);
    
            cout << s << "  ---  " << length << endl;
            cout << "function calls: " << function_calls << endl;
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

    //Security_Through_Obscurity();
    //Security_Through_Obscurity__Part_2();

    // Day 5
    //Hash_Password();
    //Hash_Password__Part_2();

    // Day 6
    //Signal_And_Noise();
    //Signal_And_Noise__Part_2();

    // Day 7
    //IP_Protocol_7();
    //IP_Protocol_7__Part_2();

    // Day 8
    //Two_Factor_Authentication();
    //Two_Factor_Authentication__Part_2();

    // Day 9
    //Explosives_In_Cyberspace();
    Explosives_In_Cyberspace__Part_2();

    return 0;
}
