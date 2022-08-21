#include <time.h>
#include <iostream>
#include <cstdlib>
#include <string>

std::string names[4] = {
    "Adam Smith",
    "Franz Kafka",
    "Samokhvalof Daniil",
    "Howard Lawcraft"
};

class DataPerson
{
public:
    DataPerson(const std::string&&);        

public:
    std::string name;
    short       Age ;
    short       IQ  ;   
};

DataPerson::DataPerson(const std::string&& type)
{
    if (type == "Adult")
    {
        name = names[rand() % 3 + 0];
        Age  = rand() % 50 + 18;
        IQ   = rand() % 120 + 70;
    }
}

class Person
{

private:
    static Person* _s;


// Методы
public:
    
    static void    change_person(const std::string&&);
    static Person* instance();
    
    operator=(Person&) = delete;
    Person(Person&)    = delete;    
    Person()           = default;

// Pimpl
public:
    DataPerson* data_p;
};  

Person* Person::_s = nullptr;


class Adult: public Person  
{
private:
    DataPerson* data_p = new DataPerson("Adult");
};

void Person::change_person(const std::string&& type)
{
    if (_s == nullptr) return;
    delete _s;
    
    if (type == "Adult")
        _s = new Adult;
}

Person* Person::instance()
{     
    if (_s == nullptr) _s = new Adult;
    return _s;        
}


class Script
{

};


int main()
{
    std::cout << Person::instance()->data_p->name << '\n';
    std::cout << Person::instance()->data_p->IQ   << '\n';
    std::cout << Person::instance()->data_p->Age  << '\n';
}
    // clock_t tStart = clock();
    // /*--------------------------------------*/
    
    
    // int a = 6, b = 5;
    // for(int i = 0; i < 100'000'001; i++) std::swap(a,b); 
    
    
    // /*--------------------------------------*/
    // printf("Time taken: %.10fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    // std::cout << a << '\n';
    // std::cout << b << '\n';

