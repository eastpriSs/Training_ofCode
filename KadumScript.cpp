
/* Запуск кода .ks 

<DB> - дэбаги
WORKONIT + коммент - продолжить работу

Коды исключений:

< -1  >  Проблема в файле.

Цель:

$
!num = 10; Тип данных определяеться автоматически, с помощью парс.
write("Value of num:");
write(num);
$

*/


//WORKONIT Пофиксить баг со строкой, тригерит на знак ) ИСПРАВИТЬ
#include <iostream>
#include <fstream> // Работа с файлами
#include <string>
#include <vector>
#include <cstring> // Для разбивание строк/копирования на символы, методы strcpy и c_str
//<DB>
#include <typeinfo>
// KS SYNTAX

const char START_CODE = '$'; // Только символ 
const std::string OUTPUT_METHOD = "write";

//==========================================================================

std::vector<std::string> files_strings = {};// массив со строками из файла

std::vector<char> global_array_of_char = {}; // массив символов для всех функций

/*

$
write('Hello world!');
$

*/
std::vector<std::string> doing = {}; // массив команд нужных для выполнения
// Пример {"write","'Hello world!'"}
std::vector<std::string> final_doing = {}; // массив конечных команд для выполнения
// Пример {"out","Hello world!"} <- аргумент <Hello world> без апострофов

/*Я решил создать эту со словам "А точно все работает нормально?"
В общем здесь мы еще раз анализируем xd, тока на уровне методов и функций
И добавляем в  FINAL_DOING массив
*/

void startCode(){

    std::cout << "Output is:" << "\n\n";

    for(int i = 0; i < final_doing.size(); i++){
        if(final_doing[i] == "out"){
            std::cout << final_doing[i+1] << std::endl;
        }
    }
}


void preStart(){
    // std::cout<<"doing "<<doing.size()<<std::endl; <DB>

    for(int i = 0; i < doing.size(); i++){
        if(doing[i] == OUTPUT_METHOD){

            // {"write", "Hello world!"}

            bool string_start = false;
            //Аргумент
            std::string loc_string = "";

            //Разбиваю строку на символы
            int len = doing[i+1].length();
            char local_char_array[len + 1]; // массив с символами
            std::strcpy(local_char_array, doing[i+1].c_str());

            for(int y=0; y< len; y++){
                //                               что это за хуйня? WORKONIT    
                if(local_char_array[y] == '"' or local_char_array == "'" and string_start == false){
                    string_start = true;
                    continue;
                }
                if(string_start){
                    loc_string += local_char_array[y];
                }
            }
            final_doing.push_back("out"); 
            final_doing.push_back(loc_string);
        }
    }

    startCode();

}


void analysCodeKS(){

    // Все необходимое...
    std::string func = ""; // Определяем функцию, либо метод
    std::string argumets = "";// Добавляем аргументы
    
    bool variable_name_adding = false; // Если найден символ ! и объявляеться переменная
    bool code_started = false;// Если найден символ $
    bool function_adding = true; // Добавление функции, либо метода
    bool argumets_adding = false; // Добавление аргументов к методу, либо функции
    bool string_started = false; // если работает со строкой
//  ===========================================


    for(int i =0; i < global_array_of_char.size(); i++){

        // std::cout << "func " << func << std::endl; //<DB>
        // std::cout << "args " << argumets << std::endl;//<DB>

        // std::cout << global_array_of_char[i] << std::endl; // <DB>

        char char_FOR_analys = global_array_of_char[i]; // Символ идущий дальше по массиву

        // std::cout << char_FOR_analys << std::endl; <DB>
        
        if(char_FOR_analys == START_CODE and code_started == false){
            code_started = true; // Начало анализа
            continue;
        }
        if (char_FOR_analys ==START_CODE and code_started == true){
            // for(int u = 0; u < doing.size(); u++){
            //     std::cout << doing[u] << std::endl;
            // } <DB>
            global_array_of_char.clear();// Очистка не нужной памяти
            files_strings.clear();
            preStart();
        } 

        if(code_started == true){

            //Подумать еще, пока получаеться странный код, WORKONIT, но должен работать
            //Тоесть если символ не равняеться (!) не объявляеться переменная,то определяем функцию
            // if(char_FOR_analys == '!'){
            //     variable_name_adding = true;
            // }else if(argumets_adding == false){
            //     function_adding = true;
            // }

            // if(variable_name_adding){} WORKONIT

            //Строка закончилась, возвращаем всё на прежнее место
            if(char_FOR_analys==';' and string_started == false){

                func = ""; 
                argumets = "";
                
                bool variable_name_adding = false;
                bool code_started = false;
                bool function_adding = true;
                bool argumets_adding = false;
                continue;
            }

            //Добавление аргументов
            if(argumets_adding == true){
                if(char_FOR_analys == ')'){
                    argumets_adding = false;
                    doing.push_back(argumets);
                    continue;
                }
                // if()
                argumets += char_FOR_analys;
                continue;
            }
            // Добавление методов и функций
            if(function_adding == true)
            {
                if(char_FOR_analys == '('){
                    doing.push_back(func);
                    argumets_adding = true;
                    continue;
                }
                func += char_FOR_analys;
            } 
            // write("Hello world",n) Нам нужен n как перенос строки?
            /*
            Подумай над этим(над аргументами)
            WORKONIT
            */
        }

    }
}   
// ==================================================================================
void readFile(std::string FileLink)
{

    std::string line;
 
    std::ifstream loc_file(FileLink); // окрываем файл для чтения, loc_file - объект класса
    if (loc_file.is_open())
    {
        while (getline(loc_file, line))
        {
            // std::cout << "line " <<line << std::endl; <DB>
            files_strings.push_back(line); // добавление строки 
        }
    } else{
        std::cout<< "End of program, file not found -1";
        return;
    }
    loc_file.close();     // закрываем файл
     
    // вывод вектора
    // for(int i = 0; i<files_strings.size(); i++){
    //     std::cout << files_strings[i] << std::endl;
    // } <DB>
    // Конвертируем массив строк в массив симвалов
    //=====================================================================================

    for(int i = 0; i < files_strings.size(); i++){
        std::string line_from_array = files_strings[i];

        int len = files_strings[i].length();
 
        char char_array_of_code[len + 1]; // массив с символами
    
        // Копируем содержимое строки и переводим в массив
        std::strcpy(char_array_of_code, files_strings[i].c_str());

        for (int i = 0; i < len; i++)
            global_array_of_char.push_back(char_array_of_code[i]);
    
    }

    analysCodeKS();// Если строки закончились, переходим к анализу
}

// void file_write()
// {    
//     Fstream.open(FILE); // окрываем файл для записи
//     if (Fstream.is_open()) 
//     {
//         Fstream << "" << std::endl;
//     }
//     Fstream.close();
// }


// void menu(){ // Получение имени файла и вывод инструкции к KS
//     return 0; // pass
// }

int main(){
    // std::ofstream oFile ( "Test.txt" ) ; 

    // file_write(); // запись в файл
    readFile("Test.txt"); // чтение файла
    std::cin.ignore();
}

