#include "Matrix.h"
#include <SFML/Graphics.hpp>

using MatrixStuff::Matrix;

// class Object
// {
// private:
    

// public:
//     Object(const int x = 0, const int&);
//     ~Object();
// };

// Object::Object(const int& x, const int& y)
// {
// }

// Object::~Object()
// {
// }


// Главный цикл
int main()
{
    Matrix<sf::CircleShape> brd(4,4);
    Matrix<int> n(3,3);
    n[0][1] = 2;
    n.print();

    short pos_x = 10;
    short pos_y = 10;

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++) {
            brd[i][j].setRadius(10.f);
            brd[i][j].setPosition(pos_x,pos_y);
            brd[i][j].setFillColor(sf::Color::Red);
            pos_x += 40;
        }    
        pos_x = 10;
        pos_y += 40;
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
                window.draw(brd[i][j]);

        window.display();
    }

    return 0;
}