#ifndef KWADRAT_H
#define KWADRAT_H

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics.hpp>

class Kwadrat
{
    public:
        Kwadrat(float x, float y, float szerokosc, float wysokosc, sf::Vector2f wektor, sf::Color color = sf::Color::Green);
        virtual ~Kwadrat();

        sf::Rect<float> *getRect();
        sf::RectangleShape getShape();
        void draw(sf::RenderWindow *window);
        void setColor(sf::Color color);
        void move();

        void zmienX();
        void zmienY();

    protected:

    private:
        int x;
        int y;
        int wysokosc;
        int szerokosc;

        sf::Vector2f wektor;

        sf::Rect<float> obj;
        sf::RectangleShape ksztalt;
        sf::Color color;
};

#endif // KWADRAT_H
