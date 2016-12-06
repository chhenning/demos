#include <SFML/Graphics.hpp>

#include <iostream>

using namespace std;

void offscreen_draw()
{
    sf::RenderTexture t;
    if (t.create(400, 500) == false)
    {
        // error
    }

    t.clear();
    
    
    //t.draw();
    
    t.display();

    const sf::Texture tex = t.getTexture();

    sf::Sprite s(tex);

    //window.draw(s);

}



int main()
{
    // Multiple windows are possible but each window event loop must be in the same thread in which the window was created.
    // * either the same thread
    // * each window has its own thread

    // In Windows a window shouldn't be bigger than the desktop
    sf::RenderWindow window(sf::VideoMode(400, 400), "Star Field");
    window.setPosition(sf::Vector2i(10, 50));

    sf::Vector2u size = window.getSize();
    unsigned int width = size.x;
    unsigned int height = size.y;

    // !!! never use together !!!
    window.setVerticalSyncEnabled(true);
    //window.setFramerateLimit(1);


    sf::RectangleShape shape(sf::Vector2f(10, 100));
    shape.setFillColor(sf::Color(100, 88, 231));
    shape.setPosition(sf::Vector2f(200, 100));
    shape.setOrigin(5,50);


    // run the main loop
    // must be in the same thread in which a window is created
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

        
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        sf::Vector2f coords = window.mapPixelToCoords(mouse);



        // draw it
        window.clear();
        
        shape.rotate(1);
        //shape.setRotation(45);



        window.draw(shape);
        
        // copy hidden buffer into window
        window.display();
    }



    return 0;
}