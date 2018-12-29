#include <iostream>
#include <cmath>

using namespace std;

#include <SFML/Graphics.hpp>



float length(sf::Vector2f vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}



sf::Vector2f normalize(sf::Vector2f input)
{
    return (input / length(input));
}



bool collision(sf::CircleShape& circle1, sf::CircleShape& circle2)
{
    float minDistance = circle1.getRadius() + circle2.getRadius();
    float distance = length(circle1.getPosition() - circle2.getPosition());
    return (distance < minDistance);
}



int main()
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "gRID gAME", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    sf::CircleShape player(100.f);
    player.setOrigin(player.getRadius(), player.getRadius());
    sf::CircleShape rock1(100.f);
    rock1.setOrigin(rock1.getRadius(), rock1.getRadius());
    rock1.setPosition(100, 100);
    player.setPosition(1280, 720);
    sf::RectangleShape jimmy(sf::Vector2f(2560, 1440));
    jimmy.setPosition(0, 0);
    jimmy.setFillColor(sf::Color(0, 0, 0, 30));



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
        /*
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
*/
        sf::Vector2f kbDirection(
            float(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) - float(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)),
            float(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) - float(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        );
        if (length(kbDirection)!=0.0f) player.move(normalize(kbDirection) * speed);



        if(collision(player, rock1))
        {
              player.setFillColor(sf::Color::Red);
              player.move(normalize(player.getPosition() - rock1.getPosition()) * 10.f);
        }
        else player.setFillColor(sf::Color::White);



        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();
        }
        rock1.rotate(1);

        //window.clear();
        window.draw(jimmy);
        window.draw(rock1);
        window.draw(player);
        window.display();
    }

    return 0;
}
