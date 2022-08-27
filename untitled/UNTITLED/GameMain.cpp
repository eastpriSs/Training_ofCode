#include "Matrix.h"
#include "Object.h"
#include <time.h>
#include <SFML/Graphics.hpp>

using MatrixStuff::Matrix;

class SystemAI{

public:
    SystemAI(Object*, Matrix<Object>*);
    Object* find_way();

private:
    // Наилучший выход из ситуации 
    Object* temp;
    // Начальная позиция
    Object* origin;
    // Позиции от первоначальной
    Object* left;
    Object* right;
    Object* upper;
    Object* down;

    // Получает соседей origin
    void get_neighbours();

    Matrix<Object>* board;
};

// SystemAI.CPP

void SystemAI::get_neighbours() {
    // Получаем правого соседа
    // Если мы обращаемся к объекту, находящемуся за пределами
    // поля, то соответсвенно его не существует.
    if ( board->rows() > origin->row + 1 )
        right = &(*board)[origin->column][origin->row + 1];
    
    // Левый сосед
    if ( origin->row - 1 >= 0 )
        left = &(*board)[origin->column][origin->row - 1];    

    // Нижний
    if ( origin->column + 1 < board->columns() )    
        down = &(*board)[origin->column + 1][origin->row];

    // Верхний
    if ( origin->column - 1 >= 0 )    
        upper = &(*board)[origin->column - 1][origin->row];
}

SystemAI::SystemAI(Object* o, Matrix<Object>* m)
:
    temp(nullptr),
    origin(o),
    board(m),
    right(nullptr),
    left(nullptr),
    upper(nullptr),
    down(nullptr)   
{
    get_neighbours();
}

Object* SystemAI::find_way()
{
    
    if (right){
        std::cout << 'r' << '\n';
        if ( right->symbol != ' ' ) temp = right;    
    }
    if (left){
        std::cout << 'l' << '\n';
        if ( left->symbol  != ' ' ) temp = left;    
    }
    if (down) {
        std::cout << 'd' << '\n';
        if ( down->symbol  != ' ' ) temp = down;    
    }
    if (upper) {
        std::cout << 'u' << '\n';
        if ( upper->symbol != ' ' ) temp = upper;
    }


    origin = temp;
    std::cout << "PREDICT: " << temp->symbol << '\n';
    get_neighbours();

    return temp;
}

class Player
{
public:

    Player( Object*, Matrix<Object>* );
    void draw_on(sf::RenderWindow&);
    void move();
    void place_this();

private:
    
    Matrix<Object>* board;
    Object* place_on_board;    
    
    SystemAI* ii;

    short _pos_x;
    short _pos_y;

    const short ALIGMENT_COEFFICIENT = 13;

    // Образ Player
    sf::CircleShape *body;
};

// PLAYER.CPP

inline void Player::draw_on(sf::RenderWindow& w) {
    w.draw(*body);
}

void Player::place_this() {
    _pos_x = place_on_board->x() + ALIGMENT_COEFFICIENT;
    _pos_y = place_on_board->y() + ALIGMENT_COEFFICIENT;
    
    body->setPosition(_pos_x, _pos_y);
}

void Player::move() {
    place_on_board = ii->find_way();
    place_this();
}

Player::Player(Object* place, Matrix<Object>* br )
:   
  body(new sf::CircleShape),
  board( br ),
  place_on_board( place ),
  ii( new SystemAI (place_on_board, br) ),
  _pos_x( place_on_board->x() + ALIGMENT_COEFFICIENT ),
  _pos_y( place_on_board->y() + ALIGMENT_COEFFICIENT )  

{
    body->setRadius(12);
    body->setFillColor(sf::Color(26,67,50, 150));
    body->setOutlineColor(sf::Color(26,67,160));
    body->setOutlineThickness(15);
    place_this();
}

// Главный цикл
int main()
{
    clock_t tStart;
    const size_t MATRIX_SIZE_X = 10;
    const size_t MATRIX_SIZE_Y = 10;
    Matrix<Object> brd(MATRIX_SIZE_X, MATRIX_SIZE_Y);

    sf::Vector2i position;

    short pos_x = 20;
    short pos_y = 10;

    for (size_t i = 0; i < MATRIX_SIZE_Y; i++)
    {
        for (size_t j = 0; j < MATRIX_SIZE_X; j++) {
            brd[i][j].init(i,j);
            brd[i][j].setPos(pos_x, pos_y);
            pos_x += 70;
        }    
        pos_x = 20;
        pos_y += 100;
    }

    Player pr( brd.first, &brd );

    brd.intrusive();   
    brd.first->make_alphabet();

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(15);

    bool timeStart = false;
    bool isPlayerTurn = false;

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        // brd.first->dance();
        brd.first->draw_on(window);
        pr.draw_on(window);

        if ( isPlayerTurn )
        {
            pr.move();
            isPlayerTurn = false;
        }        

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
               if ( !timeStart ) 
               { 
                    tStart = clock();
                    timeStart = true;
               }
               
               if ( brd.first->check_mouse_clicked(
                                sf::Mouse::getPosition(window)) ) {
                                    isPlayerTurn = true;
                                } 
                
            }
        }

        window.display();
    }

    Matrix<Object>::clear(brd);

    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    getchar();
    return 0;
}