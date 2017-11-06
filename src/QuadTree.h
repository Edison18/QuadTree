#ifndef QUADTREE_H
#define QUADTREE_H

#include <memory>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics.hpp>


class QuadTree: public sf::Drawable
{
    public:
        QuadTree(sf::FloatRect, int level = 0);
        virtual ~QuadTree();
        void insert(std::shared_ptr<sf::Shape> object);
        std::vector<std::shared_ptr<sf::Shape>> getObjectNeighbors(const sf::Shape& obj);
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        void clear();
        void setMaxLevels(unsigned int newMax){maxLevels = newMax;}
        void setMaxObjects(unsigned int newMax){maxObjects = newMax;}

    private:
        QuadTree(){}

        unsigned int checkInWhichNodeObjectFits(const sf::Shape& obj);
        bool objectIsOnBoundLines(const sf::Shape& obj);
        bool fitsHere(const sf::Shape& obj);

        void split();
        void reInsertContainedObjects();
        void setLevel(int l){level = l;}
        void setBounds(sf::FloatRect r){bounds = r;}
        const sf::FloatRect& getRect();

        void getObjectNeighborsRecursively(std::vector<std::shared_ptr<sf::Shape>> &vec, const sf::Shape& obj);

        unsigned int maxObjects = 5;
        unsigned int maxLevels = 15;

        unsigned int level;

        std::vector<std::shared_ptr<sf::Shape>> containedObjects;
        std::unique_ptr<QuadTree[]> nodes;
        sf::FloatRect bounds;
};

#endif // QUADTREE_H
