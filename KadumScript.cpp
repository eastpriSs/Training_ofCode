

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
#include <map> // словари
#include <iostream>
#include <fstream> // Работа с файлами
#include <string>
#include <vector>
#include <cstring> // Для разбивание строк/копирования на символы, методы strcpy и c_str
//<DB>
#include <typeinfo>
// KS SYNTAX

const char START_CODE = '$'; // Только символ 
const std::string OUTPUT_METHOD = "out";
const std::string OUTPUT_METHOD_ENTER = "lout";
// mp["привет"] = "hi";

std::vector<std::string> files_strings = {};// массив со строками из файла

std::vector<char> global_array_of_char = {}; // массив символов для всех функций


//Словари по переменные
//==========================================================================
    // Словарь под переменные типа STRING
    std::map <std::string, std::string> vrS;
    // Словарь под переменные типа INTEGER
    std::map <std::string, int> vrI;
    // Словарь под переменные типа DOUBLE WORKONIT пока под вопросом
    std::map <std::string, double> vrD;
    // Словарь под переменные типа BOOLEAN
    std::map <std::string, bool> vrB;
    // Словарь под переменные типа FLOAT WORKONIT пока под вопросом
    std::map <std::string, float> vrF;
// Доп. тема
std::map<std::string, int> names_of_all_variables;

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

    /*

        ДОБАВИТЬ ОПРЕДЕЛЕНИЯ ТИПОВ ДАННЫХ
        НУ И ПОСМОТРИ НА WORKONIT ПО ПРИКОЛУ

    */



    for(int i = 0; i < final_doing.size(); i++){
        if(final_doing[i] == "lout" || final_doing[i] == "out"){
            // Апендикс
            // ========================
            // Объяснсяю минутку БЫДЛОКОДИНГА)
            // Вообще это сделанно в благих намериньях и тут я проверяю есть ли переменная равная аргументу, который нужно вывести
            
            if(names_of_all_variables.count(final_doing[i+1]) > 0){
                if(names_of_all_variables[final_doing[i+1]] == 0){// INT
                    // Выясняем нужен ли перенос.
                    if(final_doing[i] == "lout"){
                        std::cout << vrI[final_doing[i+1]] << std::endl;
                    }
                    if(final_doing[i] == "out"){
                        std::cout << vrI[final_doing[i+1]];
                    }
                    
                }
                if(names_of_all_variables[final_doing[i+1]] == 2){// FLOAT
                    if(final_doing[i] == "lout"){
                       std::cout << vrF[final_doing[i+1]] << std::endl; 
                    }
                    if(final_doing[i] == "out"){
                        std::cout << vrF[final_doing[i+1]];
                    }
                }
                if(names_of_all_variables[final_doing[i+1]] == 3){// BOUBLE
                    if(final_doing[i] == "lout"){
                       std::cout << vrD[final_doing[i+1]] << std::endl; 
                    }
                    if(final_doing[i] == "out"){
                        std::cout << vrD[final_doing[i+1]];
                    }
                }
                if(names_of_all_variables[final_doing[i+1]] == 4){// BOOLEAN
                    if(vrB[final_doing[i+1]] == 1){
                        std::cout << "Yee, that's true!" << std::endl;
                    }
                    if(vrB[final_doing[i+1]] == 0){
                        std::cout << "Oh, that's false!" << std::endl;
                    }
                }
                if(names_of_all_variables[final_doing[i+1]] == 5){
                    if(final_doing[i] == "lout"){
                       std::cout << vrS[final_doing[i+1]] << std::endl;  // STRING
                    }
                    if(final_doing[i] == "out"){
                        std::cout << vrS[final_doing[i+1]];
                    }                    
                }
                

            }else{
                if(final_doing[i] == "lout"){
                    std::cout<< final_doing[i+1] << std::endl;
                }
                if(final_doing[i] == "out"){
                    std::cout<< final_doing[i+1];
                }
            }

            
        }
        // std::cout << final_doing[i] << " ; "; <db>
    }
    
}


void preStart(){
    // std::cout<<"doing "<<doing.size()<<std::endl;  <db>
    
    for(int i = 0; i < doing.size(); i++){
        
        // out()
        if(doing[i] == OUTPUT_METHOD){

            final_doing.push_back("out");
            final_doing.push_back(doing[i+1]);

        }
        // lout()
        if(doing[i] == OUTPUT_METHOD_ENTER){

            final_doing.push_back("lout");
            final_doing.push_back(doing[i+1]);

        }  

        // std::cout << doing[i] << " ; "; <DB>
    
        
    }

    startCode();

}




void analysCodeKS(){

    // Все необходимое...
    std::string value = ""; // 
    std::string func = ""; // Определяем функцию, либо метод
    std::string argumets = "";// Добавляем аргументы
    std::string variable_name = "";
    
    int type_of_variable_checker = 0;

    bool string_is_true = false; // если мы нашли строку
    bool value_adding = false; // Нахождение значения для переменной
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

        // std::cout << char_FOR_analys << std::endl;  //<DB>

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


            // WORKONIT

            // ## Переменные
// ==========================================================================================
            if(char_FOR_analys == '!' && string_is_true == false){
                
                function_adding = false;
                variable_name_adding = true;
                continue;
            }

            /*
            0 - Int
            2 - Float
            3 - Double
            4 - Boolean
            5 - String
            */

            // Обнаружение типов
        //===================================================

            if(value_adding == true){
                
                // !num = "Hello";
                
                // std::cout << value << std::endl; <DB>

                if(char_FOR_analys == '"' && string_is_true == false){
                    type_of_variable_checker = 5; // String
                    string_is_true = true;
                    continue;
                }
                // Апендикс
                if(string_is_true == true){
                    if(char_FOR_analys == '"'){
                        string_is_true = false;
                        continue;
                    }
                    value += char_FOR_analys;
                    continue;
                }

                // !num = 1.2; - double |  !num = 1.23; - float
                if(char_FOR_analys == '.'){
                    if(global_array_of_char[i+2] != ';' && global_array_of_char[i+2] != ' '){
                        type_of_variable_checker = 2; // float
                    }else{
                        type_of_variable_checker = 3; // double
                    }
                }

                // !num = true; !num = false;
                if(char_FOR_analys == ';'){
        
                    if(value == "true"){
                        type_of_variable_checker = 4;// boolean
                        value = "1";
                    }
                    if(value == "false"){
                        type_of_variable_checker = 4;
                        value = "0";
                    }
                        
                }

                //===============================================

                if(char_FOR_analys != ';' && char_FOR_analys != ' '){
                    value += char_FOR_analys;
                }
                
                // собираем значение
                
                //==============================================
                
                // Конец строки !num = 10; <-- Мы щяс прямо на последнем символе.
                if(string_is_true == false and char_FOR_analys == ';'){ // если ; не относиться к строке, то
                    // Пора уже добавить переменную
                    
                    if(type_of_variable_checker == 0){
                        vrI[variable_name] = std::stoi(value);
                    }
                    if(type_of_variable_checker == 2){
                        vrF[variable_name] = std::stod(value);
                    }
                    if(type_of_variable_checker == 3){
                        vrD[variable_name] = std::stod(value);
                    }
                    if(type_of_variable_checker == 4){
                        vrB[variable_name] = std::stod(value);
                    }
                    if(type_of_variable_checker == 5){
                        vrS[variable_name] = value;
                    }   

                    // last = variable_name;
                    names_of_all_variables.emplace(variable_name, type_of_variable_checker);

                    value = "";
                    variable_name = "";


                    string_is_true = false; 
                    value_adding = false; 
                    variable_name_adding = false; 
                    function_adding = true; 
                    argumets_adding = false; 
                    string_started = false;

                    continue;
                }
            }


            if(variable_name_adding == true){
                if(char_FOR_analys == '=' and variable_name_adding  == true){
                    //  !num = 10; если мы находим = то теперь добавляем значение
                    variable_name_adding = false;
                    value_adding = true;
                    continue;   
                }
                if(char_FOR_analys != ' '){
                    variable_name += char_FOR_analys;
                }       
                
                
            }
// =====================================================================================================================

            // ## Функции и методы, аргументы
//=========================================================================================================

            if(function_adding == false && argumets_adding == false && char_FOR_analys == ';'){
                function_adding = true;
                continue;
            }

            if(function_adding == true && char_FOR_analys == '(')
            {
                
                doing.push_back(func);
                argumets_adding = true;
                function_adding = false;

                func = "";

                continue;
            }

            if(function_adding == true){
                
                if(char_FOR_analys == ' '){
                    continue;
                }   

             func += char_FOR_analys;   
            }


            // value = m.at(key) <-- Получения значения
            if(argumets_adding == true){
                              
                if(char_FOR_analys == ')'){
                     
                    doing.push_back(argumets);
                    argumets = "";
                    argumets_adding = false;
                    continue;  
                }
                // Если аргумент являеться строкой write("Hello world");
                if(char_FOR_analys == '"'){
                    string_is_true = true;
                    continue;
                }
                if(string_is_true == true && char_FOR_analys == '"'){
                    string_is_true = false;
                    continue;
                }
                
                argumets += char_FOR_analys; // WORKONIT Я НЕНАВИЖУ СВОЮ ЖИЗНЬ
            }
        }

    }
    // preStart(); // Без понятия что это
}   
// ==================================================================================


void readFile(std::string FileLink){

    std::string line;
 
    std::ifstream loc_file(FileLink); // окрываем файл для чтения, loc_file - объект класса
    if (loc_file.is_open()){

        while (getline(loc_file, line))
        {
            // std::cout << "line " <<line << std::endl; <DB>
            files_strings.push_back(line); // добавление строки 
        }
    }else{
        std::cout<< "End of program, file not found -1";
        return;
    }
    loc_file.close();     // закрываем файл
     

    for(int i = 0; i < files_strings.size(); i++){
        std::string line_from_array = files_strings[i];

        int len = files_strings[i].length();
 
        char char_array_of_code[len + 1]; // массив с символами
    
        // Копируем содержимое строки и переводим в массив
        std::strcpy(char_array_of_code, files_strings[i].c_str());
        for (int i = 0; i < len; i++)
            global_array_of_char.push_back(char_array_of_code[i]);
    
    }

    analysCodeKS();
    // Если строки закончились, переходим к анализу
}

int main(){
    // fileWrite("Test.ks"); // запись в файл
    readFile("Test.ks"); // чтение файла
    std::cin.ignore();
}

