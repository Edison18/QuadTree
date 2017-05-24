#include "Kwadrat.h"

Kwadrat::Kwadrat(float x, float y, float szerokosc, float wysokosc, sf::Vector2f wektor, sf::Color color)
{
    ksztalt.setPosition(x, y);
    ksztalt.setSize(sf::Vector2f(szerokosc, wysokosc));
    ksztalt.setFillColor(color);
    this->wektor = wektor;
    obj.top = y;
    obj.left = x;
    obj.height = wysokosc;
    obj.width = szerokosc;
}

Kwadrat::~Kwadrat()
{
    //dtor
}

sf::Rect<float> *Kwadrat::getRect()
{
    return &obj;
}

void Kwadrat::draw(sf::RenderWindow* window)
{
    window->draw(ksztalt);
}

void Kwadrat::setColor(sf::Color color)
{
    ksztalt.setFillColor(color);
}

sf::RectangleShape Kwadrat::getShape()
{
    return ksztalt;
}

void Kwadrat::move()
{
    obj.top += wektor.y;
    obj.left += wektor.x;

    ksztalt.move(wektor);
}

void Kwadrat::zmienX()
{
    wektor.x*=-1;
}

void Kwadrat::zmienY()
{
    wektor.y*=-1;
}
