#include "stdafx.h"

#include "FastNoise.h"


#include "utilities.hpp"


//#include "perlin_noise.hpp"

// perlin noise was created to procedurally create textures for 3D objects, like a vase, etc.


using namespace std;

typedef unsigned char byte_t;

const int width = 1200;
const int height = 800;

struct context
{
    context()
    {
        scale = 10.f;
        columns = floor(width / scale);
        rows = floor(height / scale);

        time_offset = 0.01;

        frequency = 0.01;
    }

    byte_t* pixels;

    sf::RenderTexture render_texture;
    float scale;
    int columns;
    int rows;

    float time_offset;

    FastNoise fn;
    float frequency;
};


//inline
//void set_pixel(byte_t* pixels, const int x, const int y, const byte_t r, const byte_t g, const byte_t b, const byte_t a = 255)
//{
//    pixels[((x + y * width) * 4) + 0] = r; // red
//    pixels[((x + y * width) * 4) + 1] = g; // green
//    pixels[((x + y * width) * 4) + 2] = b; // blue
//    pixels[((x + y * width) * 4) + 3] = a; // alpha
//}

//inline
//void draw(context& c)
//{
//    for(int y = 0; y < height; ++y)
//    {
//        for(int x = 0; x < width; ++x)
//        {
//            float v = c.fn.GetNoise((float) x, (float) y);
//            byte_t g = (byte_t) processing::map(v, -1.f, 1.f, 0.f, 255);
//
//            set_pixel(c.pixels, x, y, g, g, g);
//        }
//    }
//}

inline
void draw(context& ctx)
{
    ctx.render_texture.clear();


    for(int y = 0; y < ctx.rows; ++y)
    {
        for(int x = 0; x < ctx.columns; ++x)
        {
            sf::RectangleShape r(sf::Vector2f(ctx.scale, 2));
            r.setPosition(x * ctx.scale, y * ctx.scale);

            //float v = ctx.fn.GetNoise((float) x, (float) y);
            //byte_t g = (byte_t) processing::map(v, -1.f, 1.f, 0.f, 255);
            
            float v = ctx.fn.GetNoise((float) x, (float) y, ctx.time_offset);

            r.rotate(v * 360);

            r.setFillColor(sf::Color::White);

            ctx.render_texture.draw(r);
        }
    }

    ctx.render_texture.display();

    ctx.time_offset += 0.1;
}


void run_perlin_noise__2D()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Perlin Noise");
    window.setVerticalSyncEnabled(true);

    context c;
    c.fn.SetNoiseType(FastNoise::SimplexFractal);
    c.fn.SetFrequency(0.05);

    //c.pixels = new byte_t[width * height * 4];
    //draw(c);

    //sf::Texture texture;
    //texture.create(width, height);
    //texture.setSmooth(true);

    c.render_texture.create(width, height);


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
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)
                     ||sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
                    )
                    {
                        window.close();
                    }

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    {
                        c.frequency += 0.01;
                        c.fn.SetFrequency(c.frequency);
                    }

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    {
                        c.frequency -= 0.01;
                        c.fn.SetFrequency(c.frequency);
                    }

                    break;
                }

                case sf::Event::MouseMoved:
                {
                    sf::Vector2i mouse = sf::Mouse::getPosition(window);
                    sf::Vector2f coords = window.mapPixelToCoords(mouse);

                    break;                
                }
            }
        }

        window.clear();
       
        //draw(c);
        //texture.update(c.pixels);
        //sf::Sprite sprite(texture);
        //window.draw(sprite);

        draw(c);
        sf::Sprite sprite(c.render_texture.getTexture());
        window.draw(sprite);


        
        // copy hidden buffer into window
        window.display();
    }
}
