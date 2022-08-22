#include "Matrix.h"
#include "Object.h"
#include <SFML/Graphics.hpp>

using MatrixStuff::Matrix;


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

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++) 
        {
            if (j == 0)
            {
                brd[i][j].intrusive(nullptr, &brd[i][j+1]);
                continue;
            }
            else if (j == 3)
            {
                brd[i][j].intrusive(&brd[i][j-1], nullptr);
                continue;
            }
            else
            {
                brd[i][j].intrusive(&brd[i][j-1], &brd[i][j+1]);
            }
        }    
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