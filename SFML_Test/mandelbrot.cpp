#include "stdafx.h"

#include <SFML/Graphics.hpp>

#include <chrono>
#include <iostream>

#include "utilities.hpp"


using namespace std;

using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using namespace std::literals::chrono_literals;


const int width = 800;
const int height = 800;
const float max_iterations = 1000.f;


float min_x_value = -2.5f;
float max_x_value = 2.0f;

float min_y_value = -2.0f;
float max_y_value = 2.0f;


int infinity = 16;

using namespace color;

rgb8u get_color(const int n)
{
    rgb8u colors[16] = 
    {
          {  66,  30,  15 } // brown 3
        , {  25,   7,  26 } // dark violett
        , {   9,   1,  47 } // darkest blue
        , {   4,   4,  73 } // blue 5
        , {   0,   7, 100 } // blue 4
        , {  12,  44, 138 } // blue 3
        , {  24,  82, 177 } // blue 2
        , {  57, 125, 209 } // blue 1
        , { 134, 181, 229 } // blue 0
        , { 211, 236, 248 } // lightest blue
        , { 241, 233, 191 } // lightest yellow
        , { 248, 201,  95 } // light yellow
        , { 255, 170,   0 } // dirty yellow
        , { 204, 128,   0 } // brown 0
        , { 153,  87,   0 } // brown 1
        , { 106,  52,   3 } // brown 2
    };

    return colors[n % 16];
}

void draw_mandelbrot(rgba8_image& image)
{
    //set_pixel(pixels, 799, 799, 255, 0, 0);

    // https://en.wikipedia.org/wiki/Mandelbrot_set
    // Mandelbrot is a set of complex numbers c ( the image ) for which the function f(z) = z^2 + c does not diverge when iterated from z = 0.

    // 1. define a range to work with, starting with [-2.5,2.5]
    // 2. map each pixel x and y into that space
    // 3. value a (real component) and b (imaginary component) of complex number c
    // 4. iterate to see if goes into infinity (here > 16)
    //    f(z_0) = c
    //    f(z_1) = z_0^2 + c_1 = c_1
    //    f(z_2) = z_1^2 + c = c_1^2 + c_2
    // 5. for each iteration test of f(z_n) goes into infinity (> 16 at the start)
    // 6. Use number of iterations to color a pixel

    std::vector<int> histogram(max_iterations + 1);


    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            float a = processing::map(x, 0.f, width, min_x_value, max_x_value);
            float b = processing::map(y, 0.f, height, min_y_value, max_y_value);

            float c_a = a;
            float c_b = b;

            int n = 0;

            float z = 0.f;

            // integrate 100 times
            while(n < max_iterations)
            {
                float real = (a * a) - (b * b);
                float imag = 2.f * a * b;

                a = real + c_a;
                b = imag + c_b;

                // square so that a and b are positive
                if((a * a + b * b) > infinity)
                {
                    break;
                }

                n++;
            }

            histogram[n]++;

            //float gray = ( n * 32 ) % 255;
            //assert(gray >= 0.0 && gray <= 255.0);


            if(n == 0 || n == max_iterations)
            {
                image.set_pixel(x, y, 0, 0, 0);
            }
            else
            {
                const rgb8u c = get_color(n);
                
                image.set_pixel(x, y, c.r, c.g, c.b);
            }
        }
    }
}


void run_mandelbrot()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Mandelbrot Set");

    // RGBA per pixel
    rgba8_image image(width, height);
    draw_mandelbrot(image);


    //for(int y = 0; y < height; ++y)
    //{
    //    for(int x = 0; x < width; ++x)
    //    {
    //        image.set_pixel(x, y, 255, 0, 0);
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
        bool redraw = false;
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

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                    {
                        infinity += 16;
                        redraw = true;
                    }


                    break;
                }
            }
        }

        refresh_start = Clock::now();

        window.clear();

        if(redraw)
        {
            render_start = Clock::now();
            
            draw_mandelbrot(image);
            
            render_end = Clock::now();

            show_render_time = true;
        }

        texture.update(image.pixels);

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
