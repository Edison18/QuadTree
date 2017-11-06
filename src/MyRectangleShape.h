#ifndef MYRECTANGLESHAPE_H
#define MYRECTANGLESHAPE_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "QuadTree.h"

class MyRectangleShape: public sf::RectangleShape
{
    public:
        MyRectangleShape(sf::Vector2f size, std::shared_ptr<QuadTree> quadTree);
        void update(sf::RenderWindow &window);

    private:
        sf::Vector2f direction;
        std::shared_ptr<QuadTree> quadTree;

        bool checkCollision(const std::vector<std::shared_ptr<sf::Shape>> &vec);
        void checkCollisionWithWindowBounds(sf::RenderWindow &window);
        float speed;
};

#endif // MYRECTANGLESHAPE_H
