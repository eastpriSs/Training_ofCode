#include "Matrix.h"
#include <SFML/Graphics.hpp>

using MatrixStuff::Matrix;

class Object
{
private:

    short _pos_x = 0;
    short _pos_y = 0;

    sf::RectangleShape  *back_rect;
    sf::CircleShape     *front_shape;

public:
    Object();
    void setPos(const short&, const short&) noexcept;
    void draw_on(sf::RenderWindow&) noexcept;
    ~Object() = default;
};

// OBJECT.CPP
// mtr[i][j].draw_on(win);
inline void Object::draw_on(sf::RenderWindow& w) noexcept 
{
    w.draw(*back_rect);
    w.draw(*front_shape);
}

void Object::setPos(const short& x, const short& y) noexcept {
    
    _pos_x = x;
    _pos_y = y;

    back_rect->setPosition(_pos_x, _pos_y);
    front_shape->setPosition(_pos_x, _pos_y);
}

Object::Object() 
: back_rect(new sf::RectangleShape), front_shape(new sf::CircleShape)
{
    // Прямоугольник сзади круга
    back_rect->setSize(sf::Vector2f(50, 50));
    back_rect->setOutlineColor(sf::Color::White);
    back_rect->setOutlineThickness(5);
    back_rect->setPosition(_pos_x, _pos_y);
    
    // Круг
    front_shape->setRadius(25);
    front_shape->setOutlineColor(sf::Color::Green);
    front_shape->setOutlineThickness(5);
    front_shape->setPosition(_pos_x, _pos_y);
    
}    

// Главный цикл
int main()
{
    Matrix<Object> brd(4,4);
    Matrix<int> n(3,3);
    n[0][1] = 2;
    n.print();

    short pos_x = 10;
    short pos_y = 10;

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++) {
            brd[i][j].setPos(pos_x, pos_y);
            pos_x += 100;
        }    
        pos_x = 10;
        pos_y += 100;
    }

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    window.setFramerateLimit(30);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        for (size_t i = 0; i < 4; i++)
            for (size_t j = 0; j < 4; j++)
                brd[i][j].draw_on(window);

        window.display();
    }

    return 0;
}