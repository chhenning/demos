
// Taken from 
// Coding Challenge #1: Starfield in Processing
// https://www.youtube.com/watch?v=17WoOqgXsRM&t=220s


#include <SFML/Graphics.hpp>

#include <cassert>
#include <iostream>

using namespace std;

const int view_width = 1024;
const int view_height = 640;
const int num_starts = 200;

namespace processing
{
    /// \brief Map a value from one range to another. Value can be outside its own range.
    float map(float value, float start1, float stop1, float start2, float stop2)
    {
        //assert(stop1>start1);
        //assert(stop2>start2);
        float x = value / ( stop1 - start1 );

        return start2 + ( stop2 - start2 ) * x;
    }

    float random(float low, float high)
    {
        assert(high>low);

        return (std::rand() % ((int) high - (int) low)) + low;
    }

    float random(float high)
    {
        return (std::rand() % ((int)high));
    }

}

struct Star
{
    Star() {}

    Star(const int width, const int height)
    {
        _x = processing::random(-view_width, view_width);
        _y = processing::random(-view_height, view_height);
        _z = processing::random(view_width);

        _prev_z = _z;
    }

    void update()
    {
        if(_z < 1)
        { 
            _x = processing::random(-view_width, view_width);
            _y = processing::random(-view_height, view_height);
            _z = processing::random(view_width);

            _prev_z = _z;
        }
        else
        {
            _prev_z = _z;
            //_z = _z - 10;
        }
    }

    void draw(sf::RenderTarget& target) const
    {
        float sx = processing::map(_x / _z, -1.f, 1.f, 0.f, view_width);
        float sy = processing::map(_y / _z, -1.f, 1.f, 0.f, view_height);

        float prev_x = processing::map(_x / _prev_z, -1.f, 1.f, 0.f, view_width);
        float prev_y = processing::map(_y / _prev_z, -1.f, 1.f, 0.f, view_height);

        // generate circle radius based on z. The closer/smaller z is to the viewer the bigger the radius.
        float r = processing::map(_z, 0, view_width, 8, 0);

        sf::CircleShape circle(r);
        circle.setFillColor(sf::Color(255, 255, 255));
        circle.setPosition(sf::Vector2f(sx, sy));

        circle.move(sf::Vector2f(view_width/2, view_height/2));

        //auto pos = circle.getPosition();

        sf::Vertex line[] = 
        {
            sf::Vertex(sf::Vector2f(prev_x, prev_y))
            , sf::Vertex(sf::Vector2f(sx,sy))
        };

        line[0].position += sf::Vector2f(view_width / 2, view_height / 2);
        line[1].position += sf::Vector2f(view_width / 2, view_height / 2);




        target.draw(circle);
        target.draw(line, 2, sf::Lines);
    }

    private:
    
    float _x, _y, _z;
    float _prev_z;
};



class StarField : public sf::Drawable, public sf::Transformable
{
public:

    StarField(const int count)
    {
        _stars = std::vector<Star>(count);

        for (int i = 0; i < _stars.size(); ++i)
        {
            _stars[i] = Star(view_width, view_height);
        }

    }

    void update(sf::Time elapsed)
    {
        for (int i = 0; i < _stars.size(); ++i)
        {
            Star& s = _stars.at(i);

            s.update();
        }
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.clear();
        
        // apply the transform
        states.transform *= getTransform();

        // our particles don't use a texture
        states.texture = NULL;

        for (int i = 0; i < _stars.size(); ++i)
        {
            const Star& s = _stars.at(i);
            s.draw(target);
        }
    }

private:

    std::vector<Star> _stars;
};

int main()
{
    //srand(time(NULL));
    srand(100);

    sf::RenderWindow window(sf::VideoMode(view_width, view_height), "Star Field");

    window.setVerticalSyncEnabled(true);

    StarField stars(num_starts);

    sf::Clock clock;

    // run the main loop
    // must be in the same thread in which a window is created
    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                {
                    window.close();

                    break;
                }

                case sf::Event::KeyPressed:
                {
                    window.close();

                    break;
                }
            }
        }

        window.clear();
        
        sf::Time elapsed = clock.restart();
        stars.update(elapsed);

        window.draw(stars);

        window.display();
    }

    return 0;
}