#pragma once

#include <cassert>
#include <iostream>

namespace processing
{
    /// \brief Map a value from one range to another. Value can be outside its own range.
    inline
    float map(float value, float start1, float stop1, float start2, float stop2)
    {
        float x = value / ( stop1 - start1 );

        return start2 + ( stop2 - start2 ) * x;
    }

    inline
    float random(float low, float high)
    {
        assert(high>low);

        return (std::rand() % ((int) high - (int) low)) + low;
    }

    inline
    float random(float high)
    {
        return (std::rand() % ((int)high));
    }

}

