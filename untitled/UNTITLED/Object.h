#include <iostream>
#include <SFML/Graphics.hpp>

/* 
    Класс Object может работать интрузивно, но
    поддается контролю извне. Чтобы дать "свободу"
    Object нужно преминить к объекту метод intrusive

    -- Инвариант выбрасывает исключение.
*/ 
class Object
{
private:

    short _pos_x;
    short _pos_y;

    const std::string link_font = "font/VL.ttf";

    sf::RectangleShape  *back_rect;
    sf::CircleShape     *front_shape;
    sf::Font            *fnt;
    sf::Text            *symbol_txt;

    // Свойство интрузивности
    Object *left_obj; 
    Object *right_obj;
    
    bool is_clicked;

public:
    
    char symbol;

    void setPos(const short&, const short&) noexcept;
    void draw_on(sf::RenderWindow&) noexcept;
    void invariant() const;
    void intrusive(Object* l, Object* r);
    void change_color();
    void reload_text();
    void check_mouse_clicked(const sf::Vector2i&);
    void was_clicked();
    void make_alphabet();

    Object();
    Object& operator =(Object&);
    Object& operator =(Object&&);
    ~Object() = default;
};

// OBJECT.CPP

// mtr[i][j].draw_on(win);
inline void Object::draw_on(sf::RenderWindow& w) noexcept 
{
    w.draw(*back_rect);
    w.draw(*front_shape);
    w.draw(*symbol_txt);
}

// mtr[i][j].intrusive(mtr[i][j-1], mtr[i][j+1] );
inline void Object::intrusive(Object* l, Object* r)
{
    left_obj  = l;
    right_obj = r;
    // invariant();
}

// brd[i][j].make_alphabet();
inline void Object::make_alphabet()
{
    if (left_obj) 
    {
        symbol = left_obj->symbol + 1;
        reload_text();
    }
    
    if (right_obj) right_obj->make_alphabet();
}

