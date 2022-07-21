#include <iostream>
#include <fstream>

namespace TimeKit
{

using std::ostream;

struct Hour
{
    explicit Hour(const short h)
    {
        // Инвариант
        if ( h > 12 || h < 0 ) 
            throw std::out_of_range("Hour::Hour() incorrect argumet ");

        this->value = h;
    }

    Hour& operator+=(const Hour& rhs ) 
    {
        this->value += rhs.value;
        return *this;
    }

    inline void clear() {
        value = 0;
    }

    short value = 0; 
};

struct Second
{
    explicit Second(const short s)
    {
        // Инвариант
        if ( s > 60 || s < 0 ) 
            throw std::out_of_range("Second::Second() incorrect argumet ");

        this->value = s;
    }

    inline void clear() {
        value = 0;
    } 

    short value = 0; 
    
};

struct Minute
{
    explicit Minute(const short m)
    {
        // Инвариант
        if ( m > 60 || m < 0 ) 
            throw std::out_of_range("Minute::Minute() incorrect argumet ");

        this->value = m;
    }
    short value = 0;

    inline void clear() {
        value = 0;
    }

    Minute& operator+=(const Minute& rhs ) 
    {
        this->value += rhs.value;
        return *this;
    }
    
};

ostream& operator<<(ostream &os, const Hour& rhs) {
    return os << rhs.value;
}

ostream& operator<<(ostream &os, const Minute& rhs) {
    return os << rhs.value;
}

ostream& operator<<(ostream &os, const Second& rhs) {
    return os << rhs.value;
}


// Управляющий класс, отвечает за правильный формат,
// также инвариант Минут, Секунд, Часов 
typedef struct TimeFormatHMS
{
    TimeFormatHMS(const short h,
                  const short m,
                  const short s)
    : hour(h), minutes(m), sec(s)
    {  
    }

    Hour& operator+=( Hour& rhs ) 
    {
        // Нарушает инвариант
        if ( this->hour.value + rhs.value > 23 )
            this->hour.clear();
        else 
            this->hour.value += rhs.value;
              
        return this->hour;
    }

    Minute& operator+=( Minute& rhs ) 
    {
        // Нарушает инвариант
        if ( this->minutes.value + rhs.value >= 60 )
        {
            this->minutes.value = this->minutes.value + rhs.value - 60;
            this->hour += Hour(1); 
        
        } else 
            this->minutes.value += rhs.value;
              
        return this->minutes;
    }

    Second& operator+=( Second& rhs ) 
    {
        // Нарушает инвариант
        if ( this->sec.value + rhs.value >= 60 )
        {
            this->sec.value = this->sec.value + rhs.value - 60;
            this->minutes += Minute(1); 
        
        } else 
            this->sec.value += rhs.value;
              
        return this->sec;
    }

    void HMS_print() const;   

    Hour   hour; 
    Minute minutes; 
    Second sec;

} t_HMS;


void TimeFormatHMS::HMS_print() const
{
    using std::cout;

    cout << hour << ':' << minutes << ':' << sec << '\n';   
}

} // namespace TimeKit


void parseData(std::string&& lnk, short lnnm = 0) 

// * Получает сведения о светофорах и выводит на экран 
// Аргументы: имя файла и та строка, которую нужно прочесть

{
    static std::ifstream data(lnk); // ?? если файл будет удален в процессе выполнения
    if ( !data.is_open() ){
        std::cout << "File invalid";
    }

    static std::string line; 
    static short lineNum = lnnm;

    while (std::getline(data, line))
    {
        // Area комментария в файле(должен распологаться в конце)
        if ( line[0] == '&' ) break;

        lineNum++;
        if ( line == "" ) continue; 
        if ( lineNum % 2 == 0 ) continue; // Четные строки отвечают за время
                                          // их не нужно выводить    
        std::cout << "ID: " << lineNum+1 << " -- place: " << line << '\n';
        // ID соответсвует номеру строки на которой расположенно время
    }
    
    lineNum = 0;
    data.close();
}

int main()
{
    using std::cout;
    using TimeKit::t_HMS;
    using TimeKit::Second;

    Second green(55);
    Second red(20);
    int diffHours;

    diffHours = 12*60;

    t_HMS originTime(8, 0, 0);

    parseData("Barnaul.txt");

    // for ( int i = 0; i < diffHours; i += green.value+red.value ) 
    // {
    //     originTime += green;
    //     cout << "RED -- ";
    //     originTime.HMS_print();
    //     originTime += red;
    //     cout << "GREEN -- ";
    //     originTime.HMS_print();
    // }
}
