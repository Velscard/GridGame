#include <iostream>
#include <cmath>

using namespace std;

#include <SFML/Graphics.hpp>

float length(sf::Vector2f vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}
bool collision(sf::CircleShape& circle1, sf::CircleShape& circle2)
{
    float minDistance = circle1.getRadius() + circle2.getRadius();
    sf::Vector2f circle1Mid = circle1.getPosition() + sf::Vector2f(circle1.getRadius(),circle1.getRadius());
    sf::Vector2f circle2Mid = circle2.getPosition() + sf::Vector2f(circle2.getRadius(),circle2.getRadius());
    float distance = length(circle1Mid - circle2Mid);
    return (distance < minDistance);
}
int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "gRID gAME", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    sf::CircleShape player(100.f);
    sf::CircleShape rock1(100.f);
    rock1.setPosition(0, 0);
    player.setPosition(1180, 620);



    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("C:\\Users\\TPEG\\Desktop\\Comp Sci\\GridGame\\bin\\Debug\\player.jpg"))
    {
        player.setFillColor(sf::Color::Green);
    }
    sf::Texture rockTexture;
    if (!rockTexture.loadFromFile("C:\\Users\\TPEG\\Desktop\\Comp Sci\\GridGame\\bin\\Debug\\rock.jpg"))
    {
        player.setFillColor(sf::Color::Green);
    }
    player.setTexture(&playerTexture);
    rock1.setTexture(&rockTexture);

    while (window.isOpen())
    {
        float speed = 10;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player.move(-speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player.move(speed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            player.move(0, -speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            player.move(0, speed);
        }



        if(collision(player, rock1))  player.setFillColor(sf::Color::Red);
        else                          player.setFillColor(sf::Color::White);



        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        window.clear();
        window.draw(rock1);
        window.draw(player);
        window.display();
    }

    return 0;
}
