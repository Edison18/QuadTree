#include "MyRectangleShape.h"

MyRectangleShape::MyRectangleShape(sf::Vector2f size, std::shared_ptr<QuadTree> quadTree)
:quadTree(quadTree)
{
    setSize(size);
    setOrigin(size.x/2, size.y/2);

    direction.x = rand()%2;
    direction.y = rand()%2;

    speed = 3;
}

void MyRectangleShape::update(sf::RenderWindow &window)
{
    checkCollisionWithWindowBounds(window);
    if(checkCollision(quadTree->getObjectNeighbors(*this))) setFillColor(sf::Color::Red);
    else setFillColor(sf::Color::White);
    move(direction * speed);
}

void MyRectangleShape::checkCollisionWithWindowBounds(sf::RenderWindow &window)
{
    sf::Vector2f pos = getPosition();
    if(pos.x < 0) direction.x = 1;
    if(pos.x > window.getSize().x) direction.x = -1;
    if(pos.y < 0) direction.y = 1;
    if(pos.y > window.getSize().y) direction.y = -1;
}

bool MyRectangleShape::checkCollision(const std::vector<std::shared_ptr<sf::Shape>> &vec)
{
    for(auto element: vec) if(getGlobalBounds().intersects(element->getGlobalBounds()) && element.get()!=this) return true;

    return false;
}
