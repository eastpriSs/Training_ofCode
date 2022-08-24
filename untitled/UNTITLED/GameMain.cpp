#include "Matrix.h"
#include "Object.h"
#include <SFML/Graphics.hpp>

using MatrixStuff::Matrix;


// Главный цикл
int main()
{
    const size_t MATRIX_SIZE_X = 10;
    const size_t MATRIX_SIZE_Y = 10;
    Matrix<Object> brd(MATRIX_SIZE_X, MATRIX_SIZE_Y);
    Matrix<int> n(3,3);
    n[0][1] = 2;
    n.print();

    sf::Vector2i position;

    short pos_x = 10;
    short pos_y = 10;

    for (size_t i = 0; i < MATRIX_SIZE_X; i++)
    {
        for (size_t j = 0; j < MATRIX_SIZE_Y; j++) {
            brd[i][j].setPos(pos_x, pos_y);
            pos_x += 100;
        }    
        pos_x = 10;
        pos_y += 100;
    }

    brd.intrusive();
    brd[0][0].make_alphabet();

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

        for (size_t i = 0; i < MATRIX_SIZE_X; i++)
            for (size_t j = 0; j < MATRIX_SIZE_Y; j++)
                brd[i][j].draw_on(window);

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                for (size_t i = 0; i < MATRIX_SIZE_Y; i++) {
                    for (size_t j = 0; j < MATRIX_SIZE_Y; j++) {
                        brd[i][j].check_mouse_clicked(sf::Mouse::getPosition(window));
                    }    
                }
                
            }
        }
        window.display();
    }

    return 0;
}