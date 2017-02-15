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
    window.setVerticalSyncEnabled(true);

    // ABGR per pixel
    rgba32_image img(width, height);

    img.set_pixel(255, 0, 0, 255);

    sf::Texture texture;
    texture.create(width, height);


    uint8_t alpha = 255;

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

        img.set_alpha(alpha--);
        alpha = (alpha > 0) ? alpha - 1: 255;



        texture.update((uint8_t*) img.pixels);
        sf::Sprite sprite(texture);

        window.draw(sprite, sf::BlendAlpha);
        
        // copy hidden buffer into window
        window.display();
    }
}
