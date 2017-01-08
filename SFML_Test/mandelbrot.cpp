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


const int width = 800;
const int height = 800;
const int max_iterations = 1000;


float min_value = -2.5f;
float max_value = 2.5f;
int infinity = 16;

inline
void set_pixel(byte_t* pixels, const int x, const int y, const byte_t r, const byte_t g, const byte_t b, const byte_t a = 255)
{
    pixels[((x + y * width) * 4) + 0] = r; // red
    pixels[((x + y * width) * 4) + 1] = g; // green
    pixels[((x + y * width) * 4) + 2] = b; // blue
    pixels[((x + y * width) * 4) + 3] = a; // alpha
}

void draw_mandelbrot(byte_t* pixels)
{
    //set_pixel(pixels, 799, 799, 255, 0, 0);

    // https://en.wikipedia.org/wiki/Mandelbrot_set
    // Mandelbrot is a set of comples numbers c ( the image ) for which the function f(z) = z^2 + c does not diverge when iterated from z = 0.

    // 1. define a range to work with, starting with [-2.5,2.5]
    // 2. map each pixel x and y into that space
    // 3. value a (real component) and b (imaginary component) of complex number c
    // 4. iterate to see if goes into infinity (here > 16)
    //    f(z_0) = 0
    //    f(z_1) = z_0^2 + c_1 = c_1
    //    f(z_2) = z_1^2 + c = c_1^2 + c_2
    // 5. for each iteration test of f(z_n) goes into infinity (> 16 at the start)
    // 6. Use number of iterations to color a pixel

    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            float a = processing::map(x, 0, width, min_value, max_value);
            float b = processing::map(y, 0, height, min_value, max_value);

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

                if( std::abs(a + b) > infinity)
                {
                    break;
                }

                n++;
            }

            //float gray = processing::map(n, 0, max_iterations, 0, 255);
            float gray = ( n * 32 ) % 255;
            //assert(gray >= 0.0 && gray <= 255.0);

            if(n == max_iterations)
            {
                gray = 0;
            }


            set_pixel(pixels, x, y, gray, gray, gray);
        }
    }
}


void run_mandelbrot()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Mandelbrot Set");

    // RGBA per pixel
    byte_t* pixels = new byte_t[width * height * 4];
    draw_mandelbrot(pixels);


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
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    {
                        min_value += 0.1f;
                        redraw = true;
                    }

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    {
                        min_value -= 0.1f;
                        redraw = true;
                    }


                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    {
                        max_value += 0.1f;
                        redraw = true;
                    }

                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    {
                        max_value -= 0.1f;
                        redraw = true;
                    }

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
            
            draw_mandelbrot(pixels);
            
            render_end = Clock::now();

            show_render_time = true;
        }

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
