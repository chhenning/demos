#include "stdafx.h"

using namespace std;

typedef unsigned char byte_t;

const int width = 1200;
const int height = 800;

int mouse_x_ = 0;
int mouse_y_ = 0;


inline
void set_pixel(byte_t* pixels, const int x, const int y, const byte_t r, const byte_t g, const byte_t b, const byte_t a = 255)
{
    pixels[((x + y * width) * 4) + 0] = r; // red
    pixels[((x + y * width) * 4) + 1] = g; // green
    pixels[((x + y * width) * 4) + 2] = b; // blue
    pixels[((x + y * width) * 4) + 3] = a; // alpha
}


void draw_(byte_t* pixels)
{
    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            set_pixel(pixels, x, y, 255, 0, 0);
        }
    }
}

void run_()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Perlin Noise");
    window.setFramerateLimit(30);

    byte_t* pixels = new byte_t[width * height * 4];
    draw_(pixels);

    sf::Texture texture;
    texture.create(width, height);
    texture.setSmooth(true);

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

                    mouse_x_ = coords.x;
                    mouse_y_ = coords.y;

                    break;                
                }
            }
        }


        window.clear();

            
        draw_(pixels);
        texture.update(pixels);

        sf::Sprite sprite(texture);
        window.draw(sprite);

        
        // copy hidden buffer into window
        window.display();
    }
}
