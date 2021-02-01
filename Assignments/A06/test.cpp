            ///////////////////////////////////////////////////////////////////////////////
            //                   
            // Author:           Trevor Amann
            // Email:            trevor.amann9@gmail.com
            // Label:            A03
            // Title:            SFML
            // Course:           CMPS 2143
            // Semester:         Spring 2021
            //
            // Description:
            //    The program opens a sfml window and presents a green dot. 
            //
            // Usage:
            //      You just have to run the program. 
            //
            // Files:   test.cpp
            /////////////////////////////////////////////////////////////////////////////////



#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}