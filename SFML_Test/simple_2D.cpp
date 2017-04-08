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

    rgba32_image img_1(width/2, height/2);
    rgba32_image img_2(width/2, height/2);

    img_1.set_pixel(255,   0, 0, 128);
    img_2.set_pixel(  0, 255, 0, 128);

    sf::Texture texture_1;
    texture_1.create(width/2, height/2);

    sf::Texture texture_2;
    texture_2.create(width/2, height/2);

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

        img_1.set_alpha(alpha);
        alpha = (alpha > 0) ? alpha - 1 : 255;


        texture_1.update((uint8_t*) img_1.pixels);
        sf::Sprite sprite_1(texture_1);

        texture_2.update((uint8_t*) img_2.pixels);
        sf::Sprite sprite_2(texture_2);

        sprite_1.setTextureRect(sf::IntRect(100, 100, 100, 100));
        sprite_2.setTextureRect(sf::IntRect(100, 100, 100, 100));

        sprite_1.setPosition(0,0);
        sprite_2.setPosition(50,50);

        window.draw(sprite_1, sf::BlendAlpha);
        window.draw(sprite_2, sf::BlendAlpha);
        
        // copy hidden buffer into window
        window.display();
    }
}
