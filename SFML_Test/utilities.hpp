#pragma once

#include <cassert>
#include <iostream>

namespace processing
{
    

    /// \brief Map a value from one range to another. Value can be outside its own range.
    /// \remarks An input range of [input_start, input_end] has input_end - input_start + 1 numbers. So it's equivalent to a range of [0, r], where r = input_end - input_start.
    ///          Similarly, the output range is equivalent to [0, R], where R = output_end - output_start.
    ///          An input of input is equivalent to x = input - input_start. This, from the first paragraph will translate to y = (R/r)*x. Then, we can translate the y value back to the original output range by adding output_start: output = output_start + y.
    ///          (see //http://stackoverflow.com/questions/5731863/mapping-a-numeric-range-onto-another)
    inline
    float map(float value, float start1, float stop1, float start2, float stop2)
    {
        return start2 + ((stop2 - start2) / (stop1 - start1)) * (value - start1);
    }

    /// \brief Map a value from one range to another. Value can be outside its own range.
    /// \remarks An input range of [input_start, input_end] has input_end - input_start + 1 numbers. So it's equivalent to a range of [0, r], where r = input_end - input_start.
    ///          Similarly, the output range is equivalent to [0, R], where R = output_end - output_start.
    ///          An input of input is equivalent to x = input - input_start. This, from the first paragraph will translate to y = (R/r)*x. Then, we can translate the y value back to the original output range by adding output_start: output = output_start + y.
    ///          (see //http://stackoverflow.com/questions/5731863/mapping-a-numeric-range-onto-another)
    inline
    double map(double value, double start1, double stop1, double start2, double stop2)
    {
        return start2 + ((stop2 - start2) / (stop1 - start1)) * (value - start1);
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
        return (float)(std::rand() % ((int)high));
    }
}

namespace color
{
    // http://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both

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

    inline
    hsv rgb2hsv(rgb in)
    {
        hsv         out;
        double      min, max, delta;

        min = in.r < in.g ? in.r : in.g;
        min = min  < in.b ? min  : in.b;

        max = in.r > in.g ? in.r : in.g;
        max = max  > in.b ? max  : in.b;

        out.v = max;                                // v
        delta = max - min;
        if (delta < 0.00001)
        {
            out.s = 0;
            out.h = 0; // undefined, maybe nan?
            return out;
        }
        if( max > 0.0 ) { // NOTE: if Max is == 0, this divide would cause a crash
            out.s = (delta / max);                  // s
        } else {
            // if max is 0, then r = g = b = 0              
                // s = 0, v is undefined
            out.s = 0.0;
            out.h = NAN;                            // its now undefined
            return out;
        }
        if( in.r >= max )                           // > is bogus, just keeps compilor happy
            out.h = ( in.g - in.b ) / delta;        // between yellow & magenta
        else
        if( in.g >= max )
            out.h = 2.0 + ( in.b - in.r ) / delta;  // between cyan & yellow
        else
            out.h = 4.0 + ( in.r - in.g ) / delta;  // between magenta & cyan

        out.h *= 60.0;                              // degrees

        if( out.h < 0.0 )
            out.h += 360.0;

        return out;
    }
}
