#include "Matrix.h"
#include "Object.h"
#include <time.h>
#include <SFML/Graphics.hpp>

using MatrixStuff::Matrix;


// Главный цикл
int main()
{
    clock_t tStart;
    const size_t MATRIX_SIZE_X = 10;
    const size_t MATRIX_SIZE_Y = 10;
    Matrix<Object> brd(MATRIX_SIZE_X, MATRIX_SIZE_Y);
    Matrix<int> n(3,3);
    getchar();
    n[0][1] = 2;
    n.print();

    sf::Vector2i position;

    short pos_x = 20;
    short pos_y = 10;

    for (size_t i = 0; i < MATRIX_SIZE_Y; i++)
    {
        for (size_t j = 0; j < MATRIX_SIZE_X; j++) {
            brd[i][j].setPos(pos_x, pos_y);
            pos_x += 70;
        }    
        pos_x = 20;
        pos_y += 100;
    }

    brd.intrusive();   
    brd.first->make_alphabet();

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    window.setFramerateLimit(30);

    bool timeStart = false;

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        brd.first->draw_on(window);

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
               if ( !timeStart ) 
               { 
                    tStart = clock();
                    timeStart = true;
               }
               
               brd.first->check_mouse_clicked(sf::Mouse::getPosition(window));
                
            }
        }

        window.display();
    }

    Matrix<Object>::clear(brd);

    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    getchar();
    return 0;
}