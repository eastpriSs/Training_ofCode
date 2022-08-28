#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

namespace PrivateTimeKit
{
    class Split
    {
        public:
        
        explicit Split()
        {
        }

        explicit Split( std::string& str, char sep ) {
                std::stringstream ss(str);
                std::string token;
                
                // HOURS
                std::getline(ss, token, sep);
                hr = std::stoi(token);

                // MINUTE
                std::getline(ss, token, sep);
                min = std::stoi(token);

                // SECOND
                std::getline(ss, token, sep);
                sec = std::stoi(token);

                // GREEN
                std::getline(ss, token, sep);
                green = std::stoi(token);

                // RED
                std::getline(ss, token, sep);
                red = std::stoi(token);         
            }

        static short  hr;
        static short  min;
        static short  sec;
        static short  green;
        static short  red;
    
    };

    short Split::hr    = -1;
    short Split::min   = -1;
    short Split::sec   = -1;
    short Split::green = -1;
    short Split::red   = -1;
} // PrivateTimeKit

namespace TimeKit
{

using std::ostream;
using PrivateTimeKit::Split;

struct Hour
{
    explicit Hour(const short h)
    {
        // Инвариант
        if ( h > 12 || h < 0 ) 
            throw std::out_of_range("Hour::Hour() incorrect argumet ");

        this->value = h;
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
                  const short s,
                  const short g,
                  const short r)
    : spl    (   ),      
      hour   ( h ), 
      minutes( m ), 
      sec    ( s ),
      green  ( g ),   
      red    ( r )  
    {  
    }

    
    TimeFormatHMS( std::string&& str )   // Если нам поступает формат вида: "8:0:0"
    : spl(str, separator), hour   ( Split::hr    ), 
                           minutes( Split::min   ),
                           sec    ( Split::sec   ),
                           green  ( Split::green ),
                           red    ( Split::red   )       
    {  
    }

    Hour& operator+=( Hour&& rhs ) 
    {
        // Нарушает инвариант
        if ( this->hour.value + rhs.value > 23 )
            this->hour.clear();
        else 
            this->hour.value += rhs.value;
              
        return this->hour;
    }

    Minute& operator+=( Minute&& rhs ) 
    {
        // Нарушает инвариант
        if ( this->minutes.value + rhs.value >= 60 )
        {
            this->minutes.value = this->minutes.value + rhs.value - 60;
            *this += Hour(1); 
        
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
            *this += Minute(1); // К 'этому' времени добавляем +1 мин 
        
        } else 
            this->sec.value += rhs.value;
              
        return this->sec;
    }

    void HMS_print() const; 
    void HMSGR_print() const;   

    const char separator = ':';

    Split  spl;
    Hour   hour; 
    Minute minutes; 
    Second sec;

    // Количество времени цвета
    Second green;
    Second red; 

} t_HMS;

void TimeFormatHMS::HMSGR_print() const
{
    using std::cout;

    cout << hour << ':' << minutes << ':' << sec << '|' << green << ':' << red << '\n';   
}


void TimeFormatHMS::HMS_print() const
{
    using std::cout;

    cout << hour << ':' << minutes << ':' << sec << '\n';   
}

} // namespace TimeKit



void outputManual() {
// Выводит коды для работы с меню
    using std::cout;
    
    cout << "__________________________________" << '\n';
    cout << "( * ) MANUAL FOR TERMINAL INPUT   |" << '\n';
    cout << "-----------  \'-1\' - exit          |" << '\n';
    cout << "-----------  \'0\'  - print all ids |" << '\n';

}

void outputTimetable( std::string& time_str  ) 
{
    using TimeKit::t_HMS;
    using std::cout;

    t_HMS originTime( std::move(time_str) );

    originTime.HMSGR_print();

    // Время системы
    static time_t now = time(0);
    static tm *ltm    = localtime(&now);
    // Разницу умножаем в 1.5 раза и переводим в секунды
    int diffHours     = (ltm->tm_hour - originTime.hour.value) * 2 * 3600; 

    for ( int i = 0; 
                i < diffHours; 
                        i += originTime.green.value + originTime.red.value ) 
    {
        originTime += originTime.green;
        cout << "RED -- ";
        originTime.HMS_print();
        originTime += originTime.red;
        cout << "GREEN -- ";
        originTime.HMS_print();
    }

}

void outputData(std::string&& lnk, short lnnm = -1) 

// * Получает сведения о светофорах и выводит на экран 
// Аргументы: имя файла и та строка, которую нужно прочесть
// Если lnnm не равен -1, то нужно расcчитать расписание
// определенного айди, то есть получить время на строке lnnm 

{

    static std::ifstream data;
    data.open(lnk);
    
    if ( !data.is_open() ){
        std::cout << "File invalid";
    }
    
    static std::string line; 
    static short lineNum = 0;

    while (std::getline(data, line) && lineNum != lnnm)
    {
        // Area комментария в файле(должен распологаться в конце)
        if ( line[0] == '&' ) break;
        if ( line == "" ) continue; 
        lineNum++;
        if ( lineNum % 2 == 0 ) continue;                                   // Четные строки отвечают за время
                                                                            // их не нужно выводить    
        
        std::cout << "ID: " << lineNum << " -- place: " << line << '\n';    // ID соответсвует номеру строки на которой расположенно время
                                                                            // эти данные нас больше всего интересуют
    }
    
    // Вывод расписания, передаем найденное время
    if (lnnm != -1)
        outputTimetable( line );

    lineNum = 0;
    data.close();
}

int main()
{
    using std::cout;

    // Вывод доступных светофоров
    outputData("Barnaul.txt");
    outputManual();

    int inID = 0; // Не паримся насчет исключений

    // Главный цикл
    while (inID != -1)
    {
        std::cout << "ID: ";
        std::cin >> inID;
        system("cls");
        
        if ( inID == 0 )                      // Возвращение к полному списку  
            outputData("Barnaul.txt");
        else                                 // Если указанно ID, то выводим расписание
            outputData("Barnaul.txt", inID); 

        outputManual();
    }
}

