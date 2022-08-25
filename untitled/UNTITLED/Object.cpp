#include "Object.h"

// OBJECT.CPP

void Object::was_clicked()
{
    symbol = ' ';
    is_clicked = true;
    reload_text();
    change_color();  
}    

void Object::invariant() const
{
    // // Если указатель неверен
    // if (left_obj && right_obj) // Если только ни один из не указывает на нуль
    //     if (left_obj+1 != this || right_obj-1 != this)
    //         throw std::invalid_argument("Elment of type \"OBJECT\" must be intrusive." );
}

void Object::reload_text() 
{
    delete symbol_txt;
    symbol_txt = new sf::Text;
    symbol_txt->setFont(*fnt);
    symbol_txt->setFillColor(sf::Color::Red);
    symbol_txt->setString(symbol);
    symbol_txt->setPosition(_pos_x+17, _pos_y+6);
}

Object& Object::operator =(Object& rhs)
{
    back_rect = rhs.back_rect;
    front_shape = rhs.front_shape;
    fnt = rhs.fnt;

    return *this;
}

void Object::change_color()
{
    back_rect->setFillColor(sf::Color::Blue);
    front_shape->setFillColor(sf::Color::Magenta);
}

Object& Object::operator =(Object&& rhs)
{

    back_rect = rhs.back_rect;
    front_shape = rhs.front_shape;
    fnt = rhs.fnt;

    rhs.back_rect = nullptr;
    rhs.front_shape = nullptr;
    rhs.fnt = nullptr;

    return *this;
}


void Object::setPos(const short& x, const short& y) noexcept {
    
    _pos_x = x;
    _pos_y = y;

    back_rect->setPosition(_pos_x, _pos_y);
    front_shape->setPosition(_pos_x, _pos_y);
    symbol_txt->setPosition(_pos_x+17, _pos_y+6);

}

Object::Object() 
:   
    back_rect(  new sf::RectangleShape), 
    front_shape(new sf::CircleShape),
    fnt(        new sf::Font), 
    symbol_txt( new sf::Text),  

    right_obj(nullptr),
    left_obj(nullptr),

    symbol('A'),
    is_clicked(false),

    _pos_x(0), 
    _pos_y(0)  
{

    // Прямоугольник сзади круга
    back_rect->setSize(sf::Vector2f(50, 50));
    back_rect->setOutlineColor(sf::Color::White);
    back_rect->setOutlineThickness(5);

    // Круг
    front_shape->setRadius(25);
    front_shape->setOutlineColor(sf::Color::Green);
    front_shape->setOutlineThickness(5);
    
    // Символ
    fnt->loadFromFile(link_font);
    symbol_txt->setFont(*fnt);
    symbol_txt->setFillColor(sf::Color::Red);
    symbol_txt->setString(symbol);

    back_rect->setPosition(_pos_x, _pos_y);
    front_shape->setPosition(_pos_x, _pos_y);
    symbol_txt->setPosition(_pos_x+17, _pos_y+6);

}    

Object::~Object()
{
    delete back_rect;
    delete front_shape;
    delete symbol_txt;
    delete fnt;
}