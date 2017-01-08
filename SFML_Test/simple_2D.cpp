#include "stdafx.h"

#include <SFML/Graphics.hpp>

#include <iostream>

#include "utilities.hpp"


using namespace std;

typedef unsigned char byte_t;

const int width = 800;
const int height = 800;
const int max_iterations = 100;

void simple_2D()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Simple 2D");

    // RGBA per pixel
    byte_t* pixels = new byte_t[width * height * 4];

    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            pixels[((x + y * width) * 4) + 0] = 255; // red
            pixels[((x + y * width) * 4) + 1] = 0; // green
            pixels[((x + y * width) * 4) + 2] = 0; // blue
            pixels[((x + y * width) * 4) + 3] = 255; // alpha
        }
    }

    sf::Texture texture;
    texture.create(width, height);


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

        texture.update(pixels);

        sf::Sprite sprite(texture);
        window.draw(sprite);

        
        // copy hidden buffer into window
        window.display();
    }
}
