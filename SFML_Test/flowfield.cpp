#include "stdafx.h"

#include "FastNoise.h"

#include "particle.hpp"
#include "utilities.hpp"

// https://youtu.be/BjoM9oKOAKY?list=PLRqwX-V7Uu6ZiZxtDDRCi6uhfTH4FilpH

using namespace std;

typedef unsigned char byte_t;

const int width = 1200;
const int height = 800;

struct context
{
    context()
    {
        scale = 20.f;
        columns = (int) floor(width / scale);
        rows = (int) floor(height / scale);

        render_texture.create(width, height);

        // particle stuff

        particles.resize(1000);
        for(int i = 0; i < particles.size(); ++i)
        {
            particles[i] = particle(processing::random(width), processing::random(height));
            //particles[i].set_vel(processing::random(-10, 10), processing::random(-10, 10));
        }

        particle_vertices = sf::VertexArray(sf::Quads, 4 * particles.size());

        // flowfield

        flowfield_vectors = sf::VertexArray(sf::Lines, 2 * columns * rows);

        flowfield.resize(columns * rows);


        // Noise stuff
        fn.SetNoiseType(FastNoise::SimplexFractal);
        fn.SetFrequency(0.05);

        frequency = 0.01;
        time_offset = 0.01;
    }

    void update_flowfield()
    {
        for(int y = 0; y < rows; ++y)
        {
            for(int x = 0; x < columns; ++x)
            {
                float pi = 3.14159265359;
                
                // [-PI,PI]
                float angle = fn.GetNoise((float) x, (float) y, time_offset) * pi;
                //float angle = -pi / 4.f;//-pi / 4.f;
                flowfield[x + y * columns].set_x(cosf(angle));
                flowfield[x + y * columns].set_y(sinf(angle));
            }
        }

        time_offset += 0.01;
    }

    void update_particles()
    {

        for(int i = 0; i < particles.size(); ++i)
        {
            float pos_x = particles[i].pos_x();
            float pos_y = particles[i].pos_y();
            
            int x = (int)(particles[i].pos_x() / scale);
            int y = (int)(particles[i].pos_y() / scale);
            
            int index = x + y * columns;
            
            vector2 v = flowfield[index];
            v.mult(0.1);

            particles[i].apply_force(v);
            particles[i].update(width, height);
        }
    }

    void draw_particles()
    {
        for(int i = 0; i < particles.size(); ++i)
        {
            //sf::CircleShape c(5);
            //c.setPosition(particles[i].pos_x(), particles[i].pos_y());
            //c.setFillColor(sf::Color::Yellow);

            //render_texture.draw(c);

            float size = 5;
            float center_x = particles[i].pos_x();
            float center_y = particles[i].pos_y();

            float lower_left_x = center_x - size / 2;
            float lower_left_y = center_y + size / 2;

            float upper_left_x = center_x - size / 2;
            float upper_left_y = center_y - size / 2;

            float upper_right_x = center_x + size / 2;
            float upper_right_y = center_y - size / 2;

            float lower_right_x = center_x + size / 2;
            float lower_right_y = center_y + size / 2;

            int index = 4 * i;

            particle_vertices[index].position.x = lower_left_x;
            particle_vertices[index].position.y = lower_left_y;
            particle_vertices[index].color = sf::Color(255,255,0,128);

            particle_vertices[index+1].position.x = upper_left_x;
            particle_vertices[index+1].position.y = upper_left_y;
            particle_vertices[index+1].color = sf::Color(255,255,0,128);

            particle_vertices[index+2].position.x = upper_right_x;
            particle_vertices[index+2].position.y = upper_right_y;
            particle_vertices[index+2].color = sf::Color(255,255,0,128);

            particle_vertices[index+3].position.x = lower_right_x;
            particle_vertices[index+3].position.y = lower_right_y;
            particle_vertices[index+3].color = sf::Color(255,255,0,128);
        }

        render_texture.draw(particle_vertices);
    }

    void draw_flowfield_vectors()
    {
        int i = 0;
        
        for(int y = 0; y < rows; ++y)
        {
            for(int x = 0; x < columns; ++x)
            {
                //sf::RectangleShape r(sf::Vector2f(scale, 1));
                //r.setPosition(x * scale, y * scale);
                //float v = fn.GetNoise((float) x, (float) y, time_offset);
                //r.rotate(v * 360);
                //r.setFillColor(sf::Color(255,255,255, 100));

                //render_texture.draw(r);

                vector2 a(x * scale, y * scale);
                vector2 b(x * scale + scale, y * scale);

                const vector2& v = flowfield[x + y * columns];
                float angle = atan2f(v.get_x(), v.get_y());
                
                b.rotate(a, angle);

                flowfield_vectors[i].position = sf::Vector2f(a.get_x(), a.get_y());
                flowfield_vectors[i+1].position = sf::Vector2f(b.get_x(), b.get_y());

                flowfield_vectors[i].color = sf::Color::White;
                flowfield_vectors[i+1].color = sf::Color::White;

                i+=2;
                

            }
        }

        render_texture.draw(flowfield_vectors);
    }

    void update()
    {
        update_flowfield();
        update_particles();
    }
    
    void draw()
    {
        render_texture.clear();

        //draw_flowfield_vectors();
        draw_particles();

        render_texture.display();
    }


    sf::RenderTexture render_texture;
    float scale;
    int columns;
    int rows;


    std::vector<particle> particles;
    
    // made up from points
    sf::VertexArray particle_vertices;

    // displayed as line segments
    sf::VertexArray flowfield_vectors;

    std::vector<vector2> flowfield;


    FastNoise fn;
    float frequency;
    float time_offset;
};

void run_flowfield()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Flowfield");
    window.setVerticalSyncEnabled(true);

    context c;
    
    sf::Texture background;
    background.create(width, height);

    sf::Image img;
    img.create(width, height);

    for(int y = 0; y < img.getSize().y; ++y)
    {
        for(int x = 0; x < img.getSize().x; ++x)
        {
            img.setPixel(x,y, sf::Color(255, 0, 0, 128));
        }
    }



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

        
        //background.update(window);
        //sf::Image i = background.copyToImage();

        //for(int y = 0; y < img.getSize().y; ++y)
        //{
        //    for(int x = 0; x < img.getSize().x; ++x)
        //    {
        //        //sf::Color c = img.getPixel(x, y);
        //        i.setPixel(x,y, sf::Color(255, 0, 0, 128));
        //    }
        //}
        
        background.loadFromImage(img);

        c.update();

        window.clear();
       
        c.draw();

        sf::Sprite background_sprite(background);
        sf::Sprite sprite(c.render_texture.getTexture());
        

        window.draw(background_sprite, sf::BlendAlpha);
        window.draw(sprite, sf::BlendAlpha);


        // copy hidden buffer into window
        window.display();
    }
}
