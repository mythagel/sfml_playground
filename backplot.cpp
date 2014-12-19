#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML Basic");

    std::vector<sf::Vertex> vertices;
    vertices.push_back(sf::Vector3f(0,0,0));
    vertices.push_back(sf::Vector3f(10,0,0));
    vertices.push_back(sf::Vector3f(10,10,0));
    vertices.push_back(sf::Vector3f(0,10,0));


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(&vertices[0], vertices.size(), sf::Lines);
        window.display();
    }

    return 0;
}
