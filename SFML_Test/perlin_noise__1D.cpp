#include "stdafx.h"

#include "FastNoise.h"


#include "utilities.hpp"


//#include "perlin_noise.hpp"

// perlin noise was created to procedurally create textures for 3D objects, like a vase, etc.


using namespace std;

typedef unsigned char byte_t;

const int width = 1200;
const int height = 800;

int perlin_noise_mouse_x = 0;
int perlin_noise_mouse_y = 0;


FastNoise fn;
float start = 0.0f;

void draw_perlin_noise__1D(sf::RenderTexture& render_texture)
{
    vector<sf::Vertex> vertices(width);

    float x_offset = start;

    for(int x = 0; x < width; ++x)
    {
        //float a = sinf(x_offset);
        float a = fn.GetNoise(x_offset, 0.f);
        x_offset += 1.f;

        float b = processing::map(a, -1.f, 1.f, 0.f, height / 2);

        vertices[x] = sf::Vertex(sf::Vector2f(x, b), sf::Color::White);
    }

    start += 1.8;

    render_texture.clear();
    render_texture.draw(&vertices[0], vertices.size(), sf::LinesStrip);
    render_texture.display();
}


void run_perlin_noise__1D()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Perlin Noise");
    window.setVerticalSyncEnabled(true);

    fn.SetNoiseType(FastNoise::SimplexFractal);

    sf::RenderTexture render_texture;
    render_texture.create(width, height);
    render_texture.setSmooth(true);

    draw_perlin_noise__1D(render_texture);

    //vector<sf::Vertex> vertices;
    //vertices.push_back(sf::Vertex(sf::Vector2f(10, 10), sf::Color::Red));
    //vertices.push_back(sf::Vertex(sf::Vector2f(100, 100), sf::Color::Red));
    //vertices.push_back(sf::Vertex(sf::Vector2f(200, 250), sf::Color::Red));

    //render_texture.draw(&vertices[0], vertices.size(), sf::LinesStrip);
    //render_texture.display();


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

                    break;
                }

                case sf::Event::MouseMoved:
                {
                    sf::Vector2i mouse = sf::Mouse::getPosition(window);
                    sf::Vector2f coords = window.mapPixelToCoords(mouse);

                    perlin_noise_mouse_x = coords.x;
                    perlin_noise_mouse_y = coords.y;

                    break;                
                }
            }
        }

        window.clear();
       
        draw_perlin_noise__1D(render_texture);

        sf::Sprite sprite(render_texture.getTexture());
        window.draw(sprite);

        
        // copy hidden buffer into window
        window.display();
    }
}
