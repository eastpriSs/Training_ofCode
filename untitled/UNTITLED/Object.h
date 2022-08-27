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

    short lenght_a;
    short lenght_b;
    short row;
    short column; 

    void setPos(const short&, const short&) noexcept;
    
    void draw_on(sf::RenderWindow&) noexcept;
    void invariant() const;
    void intrusive(Object* l, Object* r);
    void change_color();
    void reload_text();
    bool check_mouse_clicked(const sf::Vector2i&);
    void was_clicked();
    void make_alphabet();
    void dance();
    void init(const short&, const short&);

    const short& x() const;
    const short& y() const; 

    Object();
    Object& operator =(Object&);
    Object& operator =(Object&&);
    ~Object();
};

// OBJECT.CPP

inline const short& Object::x() const {
    return _pos_x;
}

inline const short& Object::y() const {
    return _pos_y;
}     

inline void Object::init(const short& c, const short& r) {
    column = c; row = r; 
}

// mtr[i][j].draw_on(win);
inline void Object::draw_on(sf::RenderWindow& w) noexcept 
{
    w.draw(*back_rect);
    w.draw(*front_shape);
    w.draw(*symbol_txt);
    
    if (right_obj) right_obj->draw_on(w);
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


inline bool Object::check_mouse_clicked(const sf::Vector2i& cl)
{ 
    if (cl.x > _pos_x && cl.x < _pos_x+50) {
        if (cl.y > _pos_y && cl.y < _pos_y+50) {
            was_clicked();
            return true;
        }
    }
    
    if (right_obj) right_obj->check_mouse_clicked(cl);
        else return false;
    
    return true;
}

inline void Object::dance()
{   
    // Шанс 30 %
    if ( (rand()% 3 + 1) == 2 ) 
    {
        back_rect->setFillColor(sf::Color(rand()% 255,rand()% 255,rand()% 255));
        front_shape->setFillColor(sf::Color(rand()% 255,rand()% 255,rand()% 255));
    }
    
    if (right_obj) right_obj->dance();
}
