#pragma once

/// \brief vector2 is an arrow in 2D space with it's tail sitting on the origin
struct vector2
{
    vector2()
    : x(0.f)
    , y(0.f)
    {}
    
    vector2(float x, float y)
    : x(x)
    , y(y)
    {}

    void add(const float value)
    {
        x += value;
    }

    void add(const vector2& other)
    {
        x += other.x;
        y += other.y;
    }

    void sub(const vector2& other)
    {
        x -= other.x;
        y -= other.y;
    }

    void mult(float f)
    {
        x *= f;
        y *= f;
    }

    /// \see http://stackoverflow.com/questions/2259476/rotating-a-point-about-another-point-2d
    void rotate(const vector2 pivot, float rad)
    {
        float s = sin(rad);
        float c = cos(rad);

        float c_x =  x - pivot.get_x();
        float c_y =  y - pivot.get_y();
    
        float x_new = (c * c_x) - (s * c_y);
        float y_new = (s * c_x) + (c * c_y);

        x = x_new + pivot.get_x();
        y = y_new + pivot.get_y();
    }

    float get_magnitude() const
    {
        return sqrtf(x * x + y * y);
    }

    float get_x() const {return x; }
    float get_y() const {return y; }

    void set_x(float v) { x = v; }
    void set_y(float v) { y = v; }


private:

    float x;
    float y;
};


// taken from Nature Of Code

struct particle
{
    particle()
    : pos()
    , vel()
    , acc()
    {}

    particle(float pos_x, float pos_y)
    : pos(pos_x, pos_y)
    , vel()
    , acc()
    {}

    void update(float width, float height)
    {
        vel.add(acc);
        pos.add(vel);
        acc.mult(0.f);

        if(pos.get_x() < 0) { pos.set_x(width - 1); }
        else if(pos.get_x() > width) { pos.set_x(0); }

        if(pos.get_y() < 0) { pos.set_y(height - 1); }
        else if(pos.get_y() > height) { pos.set_y(0); }

        if(vel.get_x() > 4) { vel.set_x(4); }
        if(vel.get_y() > 4) { vel.set_y(4); }

    }

    // http://natureofcode.com/book/chapter-2-forces/
    void apply_force(const vector2& force)
    {
        acc.add(force);
    }

    float pos_x() const { return pos.get_x(); }
    float pos_y() const { return pos.get_y(); }

    void set_vel(float x, float y) 
    { 
        vel.set_x(x); 
        vel.set_y(y); 
    }


private:

    // position
    vector2 pos;

    // velocity
    vector2 vel;

    // acceleration
    vector2 acc;
};


