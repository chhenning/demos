#include "stdafx.h"

using namespace std;

typedef unsigned char byte_t;

const int width = 1200;
const int height = 800;

int mouse_x_ = 0;
int mouse_y_ = 0;

void draw_(sf::RenderTexture& render_texture)
{
    vector<sf::Vertex> vertices(width);

    for(int x = 0; x < width; ++x)
    {
        vertices[x] = sf::Vertex(sf::Vector2f(x, 10), sf::Color::White);
    }

    render_texture.clear();
    render_texture.draw(&vertices[0], vertices.size(), sf::LinesStrip);
    render_texture.display();
}

void run_()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Perlin Noise");
    window.setFramerateLimit(30);

    sf::RenderTexture render_texture;
    render_texture.create(width, height);
    render_texture.setSmooth(true);

    draw_(render_texture);

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

            
        draw_(render_texture);
           

        sf::Sprite sprite(render_texture.getTexture());
        window.draw(sprite);

        
        // copy hidden buffer into window
        window.display();
    }
}
