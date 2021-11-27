#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    printf("Enter move speed for player : ");
    float moveSpeed;
    std::cin >> moveSpeed;

    sf::RenderWindow window(sf::VideoMode(512, 512), "SFML works!", sf::Style::Fullscreen);
    sf::RectangleShape square(sf::Vector2f(100.0f, 100.0f));
    square.setFillColor(sf::Color::Cyan);

    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::Resized:
                printf("New window width : %d, new window height : %d\n", evnt.size.width, evnt.size.height);
                break;

            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            square.move(-moveSpeed, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            square.move(moveSpeed, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            square.move(0.1f, -moveSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            square.move(0.0f, moveSpeed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            window.close();
        }

        window.clear();
        window.draw(square);
        window.display();
      
    }

    return 0;
}