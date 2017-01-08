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

namespace color
{
    struct rgb
    {
        double r; // percent
        double g; // percent
        double b; // percent
    };

    struct hsv
    {
        double h; // angle in degrees
        double s; // percent
        double v; // percent
    };


    inline
    rgb hsv2rgb(hsv in)
    {
        double      hh, p, q, t, ff;
        long        i;
        rgb         out;

        if(in.s <= 0.0) {       // < is bogus, just shuts up warnings
            out.r = in.v;
            out.g = in.v;
            out.b = in.v;
            return out;
        }
        hh = in.h;
        if(hh >= 360.0) hh = 0.0;
        hh /= 60.0;
        i = (long)hh;
        ff = hh - i;
        p = in.v * (1.0 - in.s);
        q = in.v * (1.0 - (in.s * ff));
        t = in.v * (1.0 - (in.s * (1.0 - ff)));

        switch(i) {
        case 0:
            out.r = in.v;
            out.g = t;
            out.b = p;
            break;
        case 1:
            out.r = q;
            out.g = in.v;
            out.b = p;
            break;
        case 2:
            out.r = p;
            out.g = in.v;
            out.b = t;
            break;

        case 3:
            out.r = p;
            out.g = q;
            out.b = in.v;
            break;
        case 4:
            out.r = t;
            out.g = p;
            out.b = in.v;
            break;
        case 5:
        default:
            out.r = in.v;
            out.g = p;
            out.b = q;
            break;
        }
        return out;     
    }
}
