#include <SFML/Graphics.hpp>
#include "QuadTree.h"
#include "MyRectangleShape.h"
#include <ctime>
#include <stdlib.h>
#include <sstream>

using namespace std;

class MyRectangleShape;

sf::Vector2i windowSize(800, 600);

shared_ptr<QuadTree> quadTree(new QuadTree({0, 0, (float)windowSize.x, (float)windowSize.y}));
vector<shared_ptr<MyRectangleShape>> rects;

sf::Clock deltaClock;


sf::Vector2f mousePosition(sf::RenderWindow &window)
{
    sf::Vector2f pos;
    pos.x = sf::Mouse::getPosition(window).x;
    pos.y = sf::Mouse::getPosition(window).y;

    return pos;
}

shared_ptr<MyRectangleShape> spawnRectangle(sf::Vector2f position)
{
    shared_ptr<MyRectangleShape> k(new MyRectangleShape(sf::Vector2f(20, 20), quadTree));
    k->setPosition(position);
    return k;
}

void processEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if(event.type == sf::Event::MouseButtonPressed)
            rects.push_back(spawnRectangle(mousePosition(window)));
    }
}

void update(sf::RenderWindow &window)
{
    quadTree->clear();
    try{
        for(auto element: rects) quadTree->insert(element);
    }catch(const exception &e){
        cerr<<e.what()<<endl;
    }

    for(auto element: rects) element->update(window);
}

void draw(sf::RenderWindow &window)
{
    for(auto element: rects) window.draw(*element);
    window.draw(*quadTree);
}

int main()
{
    srand( time( NULL ) );

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "QuadTree");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        deltaClock.restart();

        window.clear();

        processEvents(window);
        update(window);
        draw(window);

        window.display();
    }

    return 0;
}
