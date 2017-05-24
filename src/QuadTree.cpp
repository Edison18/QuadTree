#include "QuadTree.h"

QuadTree::QuadTree(sf::FloatRect bounds, int level)
:level(level),bounds(bounds)
{

}

std::vector<std::shared_ptr<sf::Shape>> QuadTree::getObjectNeighbors(const sf::Shape& obj)
{
    std::vector<std::shared_ptr<sf::Shape>> vec;

    getObjectNeighborsRecursively(vec, obj);

    return vec;
}

void QuadTree::getObjectNeighborsRecursively(std::vector<std::shared_ptr<sf::Shape>> &vec, const sf::Shape& obj)
{
    if(fitsHere(obj))
    {
        for(auto element: containedObjects) vec.push_back(element);
        if(nodes) for(int i = 0; i < 4; i++) nodes[i].getObjectNeighborsRecursively(vec, obj);
    }
}

QuadTree::~QuadTree()
{
    clear();
}

void QuadTree::clear()
{
    containedObjects.clear();
    nodes.reset(nullptr);
}

void QuadTree::insert(std::shared_ptr<sf::Shape> obj)
{
    if(!nodes)
    {
        containedObjects.push_back(obj);

        if(containedObjects.size() > maxObjects && level < maxLevels)
        {
            split();
            reInsertContainedObjects();
        }
    }
    else
    {
        if(objectIsOnBoundLines(*obj)) containedObjects.push_back(obj);
        else nodes[checkInWhichNodeObjectFits(*obj)].insert(obj);
    }
}

void QuadTree::reInsertContainedObjects()
{
    unsigned int i = containedObjects.size();
    for(; i > 0; i--)
    {
        std::shared_ptr<sf::Shape> tmpObj(containedObjects.back());
        containedObjects.pop_back();
        insert(tmpObj);
    }
}

unsigned int QuadTree::checkInWhichNodeObjectFits(const sf::Shape& obj)
{
    for(int i = 0; i < 4; i++)
        if(nodes[i].fitsHere(obj)) return i;

    throw std::runtime_error("Object is out of QuadTree bounds!");
}

bool QuadTree::objectIsOnBoundLines(const sf::Shape& obj)
{
    char intersections = 0;
    for(char i = 0; i < 4; i++) intersections += nodes[i].fitsHere(obj);
    if (intersections > 1) return true;
    return false;
}

bool QuadTree::fitsHere(const sf::Shape& obj)
{
    return obj.getGlobalBounds().intersects(bounds);
}

void QuadTree::split()
{
    float subWidth = (bounds.width / 2);
    float subHeight = (bounds.height / 2);
    float x = bounds.left;
    float y = bounds.top;

    nodes.reset(new QuadTree[4]);

    nodes[0].setLevel(level + 1);
    nodes[1].setLevel(level + 1);
    nodes[2].setLevel(level + 1);
    nodes[3].setLevel(level + 1);


    nodes[0].setBounds({x + subWidth, y, subWidth, subHeight});
    nodes[1].setBounds({x, y, subWidth, subHeight});
    nodes[2].setBounds({x, y + subHeight, subWidth, subHeight});
    nodes[3].setBounds({x + subWidth, y + subHeight, subWidth, subHeight});
}

const sf::FloatRect& QuadTree::getRect()
{
    return bounds;
}

void QuadTree::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(!nodes) return;

    sf::VertexArray lines(sf::Lines, 4);
    lines[0].position = sf::Vector2f(bounds.left + bounds.width/2, bounds.top);
    lines[1].position = sf::Vector2f(bounds.left + bounds.width/2, bounds.top + bounds.height);
    lines[2].position = sf::Vector2f(bounds.left, bounds.top + bounds.height/2);
    lines[3].position = sf::Vector2f(bounds.left + bounds.width, bounds.top + bounds.height/2);

    for(int i = 0; i<4; i++) nodes[i].draw(target, states);

    target.draw(lines, states);
}
