#include "stdafx.h"

#include <SFML/Graphics.hpp>

#include <chrono>
#include <iostream>

#include "utilities.hpp"


using namespace std;

typedef unsigned char byte_t;

using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using namespace std::literals::chrono_literals;


const int width = 1200;
const int height = 800;
const int max_iterations = 100;


float plane_width = 5;

float js_infinity = 16.f;


int mouse_x = 0;
int mouse_y = 0;

float angle = 0.f;


inline
void set_pixel(byte_t* pixels, const int x, const int y, const byte_t r, const byte_t g, const byte_t b, const byte_t a = 255)
{
    pixels[((x + y * width) * 4) + 0] = r; // red
    pixels[((x + y * width) * 4) + 1] = g; // green
    pixels[((x + y * width) * 4) + 2] = b; // blue
    pixels[((x + y * width) * 4) + 3] = a; // alpha
}

void draw_julia_set(byte_t* pixels)
{
    // if c_b ( the imaginary compoent) is 0 the resulting julia is perfectly symmetrical 
    
    //float c_a = processing::map(mouse_x, 0, width, -1.f, 1.f);
    //float c_b = processing::map(mouse_y, 0, height, -1.f, 1.f);

    //float c_a = cosf(angle * 3.213f);
    //float c_b = sinf(angle);;

    float c_a = -0.4;
    float c_b = 0.6;



    // http://paulbourke.net/fractals/juliaset/
    // https://en.wikipedia.org/wiki/Julia_set
    // c is a constant, like c=-0.70176-0.3842i


    // define a complex plane with just one number w
    // w can then be used for zooming
    float plane_height = (plane_width * height) / width;

    float plane_x_min = -plane_width / 2.f;
    float plane_y_min = -plane_height / 2.f;

    float plane_x_max = plane_x_min + plane_width;
    float plane_y_max = plane_y_min + plane_height;

    float plane_dx = ( plane_x_max - plane_x_min ) / width;
    float plane_dy = ( plane_y_max - plane_y_min ) / height;

    float plane_y = plane_y_min;
    for(int y = 0; y < height; ++y)
    {
        float plane_x = plane_x_min;
        for(int x = 0; x < width; ++x)
        {
            float a = plane_x;
            float b = plane_y;

            int n = 0;

            // integrate 100 times
            while(n < max_iterations)
            {
                float real = (a * a) - (b * b);
                float imag = 2.f * a * b;

                a = real + c_a;
                b = imag + c_b;

                // square so that a and b are positive
                if((a * a + b * b) > js_infinity)
                {
                    break;
                }

                n++;
            }


            // color pixel

            if(n == max_iterations)
            {
                set_pixel(pixels, x, y, 0, 0, 0);
            }
            else
            {
                float gray = ( n * 32 ) % 255;
                //double hue = ( n * 32 ) % 360;
                double hue = sqrt(((double) n) / max_iterations) * 360.0;

                color::hsv hsv_color = { hue, 1.0, 1.0 };
                color::rgb c = color::hsv2rgb(hsv_color);
            
                c.r *= 255.0;
                c.g *= 255.0;
                c.b *= 255.0;

                set_pixel(pixels, x, y, c.r, c.g, c.b);
                //set_pixel(pixels, x, y, gray, gray, gray);
            }

            plane_x += plane_dx;
        }

        plane_y += plane_dy;
    }
}


void run_julia_set()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Julia Set");
    window.setFramerateLimit(30);


    // RGBA per pixel
    byte_t* pixels = new byte_t[width * height * 4];
    draw_julia_set(pixels);


    //for(int y = 0; y < height; ++y)
    //{
    //    for(int x = 0; x < width; ++x)
    //    {
    //        set_pixel(pixels, x, y, 255, 0, 0);
    //    }
    //}



    sf::Texture texture;
    texture.create(width, height);
    texture.setSmooth(true);

    time_point<Clock> render_start = Clock::now();
    time_point<Clock> render_end = Clock::now();
    time_point<Clock> refresh_start = Clock::now();
    time_point<Clock> refresh_end = Clock::now();

    while (window.isOpen())
    {
        angle += 0.03;
        plane_width -= 0.03;

        bool show_render_time = false;

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
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                    {
                        window.close();
                    }

                    break;
                }

                case sf::Event::MouseMoved:
                {
                    sf::Vector2i mouse = sf::Mouse::getPosition(window);
                    sf::Vector2f coords = window.mapPixelToCoords(mouse);

                    mouse_x = coords.x;
                    mouse_y = coords.y;

                    break;                
                }
            }
        }

        refresh_start = Clock::now();

        window.clear();


        render_start = Clock::now();
            
        draw_julia_set(pixels);
            
        render_end = Clock::now();



        texture.update(pixels);

        sf::Sprite sprite(texture);
        window.draw(sprite);

        
        // copy hidden buffer into window
        window.display();

        refresh_end = Clock::now();

        if(show_render_time)
        {
            milliseconds render_diff = duration_cast<milliseconds>(render_end - render_start);
            milliseconds refresh_diff = duration_cast<milliseconds>(refresh_end - refresh_start);

            std::cout << "Render time: " << render_diff.count() << "ms" << std::endl;
            std::cout << "Refresh time: " << refresh_diff.count() << "ms" << std::endl;
        }
    }
}
