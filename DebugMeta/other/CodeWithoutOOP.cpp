
// Проверить все ли норм работает 

#include <map> // словари
#include <iostream>
#include <fstream> // Работа с файлами
#include <string>
#include <vector>
#include <cstring> // Для разбивание строк/копирования на символы, методы strcpy и c_str
#include <regex> // Регулярки
#include <windows.h> // Жалуется антивирус

// g++ -o -static-libgcc -static-libstdc++ DebugMeta.exe DebugMeta.cpp 

// Параметры запуска и настройки
const bool DebugMetaSwitch = false;

// Текст исключений WORKONIT добавить функцию оброботчика исключений. Что это за бред? Убрать это.
const std::string TypeError = "\nTypeError\n";

// Типы данных
const int NON_TYPE = 0; // Нету типа.
const int _INT = 1; 
const int _FLOAT = 2;
const int _DOUBLE = 3;
const int _BOOLEAN = 4;
const int STRING = 5;
const int LIST = 6; // Еще есть под типы.

const int LIST_INT = 61;
const int LIST_FLOAT = 62;
const int LIST_DOUBLE = 63;
const int LIST_BOOLEAN = 64;
const int LIST_STRING = 65;

// Синтаксис 
const char POINT_SYN_CHAR = ':'; 
const char START_CODE = '$'; // Только символ 
const std::string FOR_SYN = "for"; // WORKONIT
const std::string OUTPUT_METHOD = "out";
const std::string OUTPUT_METHOD_ENTER = "lout";
const std::string INPUT_METHOD = "get"; 
const std::string DB_METHOD_ID = "typeID"; 
const std::string SPEED_PRINT = "sout";
const std::string IF_SYN = "if";
const std::string ANGEL_FUNCTION = "angela";
const std::string LIST_FROM = "from";
const std::string STOP_SCRIPT = "st";
const std::string CRASH_SCRIPT = "cr";

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
 // Словарь под списки
    std::map <std::string, std::vector<int>> vrLi;// LIST INT
    std::map <std::string, std::vector<float>> vrLf;// LIST FLOAT
    std::map <std::string, std::vector<double>> vrLd;// LIST DOUBLE
    std::map <std::string, std::vector<bool>> vrLb;// LIST BOOLEAN
    std::map <std::string, std::vector<std::string>> vrL;// LIST STRING


// Пара: название переменной и тип данных
std::map<std::string, int> namesOfAllVariables;

// Почему не константа ? - Да потому, что этот код на плюсах
std::map<std::string, int> amountOfArgumentsForEachMethod = 
{
    {SPEED_PRINT, 2}, // sout("hello world!", 300); <- строка и дальше задержка перед выводом.
    {OUTPUT_METHOD, 1}, // out("hello world!")
    {OUTPUT_METHOD_ENTER, 1} // lout("hello world");

};

// Счетчик статистики
struct DebugMetaStatictics
{
    int countSmbls = 0;// символов пропарсил
    int countCalls = 0;// кол-во вызовов

};


// Проверяем есть ли символ в векторе символов
bool CheckElem(char NeedToFind, const std::vector<char> &List){
    for(int num = 0; num < List.size(); num++){
        if(List[num] == NeedToFind){
            return true;
        }
    }
    return false;
}
// <DB> для дэбага
void writevec(std::vector<auto> vec){
    for(int elem = 0; elem < vec.size(); elem++){
        std::cout << elem << " . " <<  vec[elem] << " | ";  
    }
    std::cout << std::endl;
}

auto returnTop(std::vector<auto> vec){
    return vec[vec.size()-1];
}

// Вывод списка
void printList(const std::vector<auto> &Vec){
    for(int N = 0; N < Vec.size(); N++){
        if(Vec.size() == N+1){
            std::cout << Vec[N];
        }else{
            std::cout <<  Vec[N] << ",";
        }  
    }
}
// Созданно для вывода содержимого переменной, вспомогательная функция для вывода
void printValueOfVar(int typeOfVar, std::string nameVar){

    switch (typeOfVar)
    {
        case _INT:
            std::cout << vrI[nameVar];
            break;
        case _FLOAT:
            std::cout << vrF[nameVar];
            break;
        case _DOUBLE:
            std::cout << vrD[nameVar];
            break;    
        case _BOOLEAN:
            std::cout << vrB[nameVar];
            break;    
        case STRING:
            std::cout << vrS[nameVar];
            break;    
        case LIST:
            printList(vrL[nameVar]);      
            break;
        case LIST_INT:
            printList(vrLi[nameVar]);
            break;
        case LIST_FLOAT:
            printList(vrLf[nameVar]);
            break;
        case LIST_DOUBLE:
            printList(vrLd[nameVar]);
            break;
        case LIST_BOOLEAN:
            printList(vrLb[nameVar]);
            break;      
    }
}

// Функция вывода
// typeOfOutput:
// 1 - с переносом
// 0 - без переноса
void OutputMethod(std::string str, int typeOfOutput)
{
    // Если аргумент - это переменная
    if(namesOfAllVariables[str] != 0){
        switch (namesOfAllVariables[str])
        {
        case _INT: str = std::to_string(vrI[str]); // INT
            break;
        case _FLOAT: str = std::to_string(vrF[str]); // FLOAT
            break;
        case _DOUBLE: str = std::to_string(vrD[str]); // DOUBLE
            break;
        case _BOOLEAN: str = std::to_string(vrB[str]); // BOOLEAN
            break;
        case STRING: str = vrS[str]; // String
            break; 
        case LIST_INT: printList(vrLi[str]);
            break;
        case LIST_FLOAT: printList(vrLf[str]);
            break;        
        case LIST_DOUBLE: printList(vrLd[str]);
            break;
        case LIST_BOOLEAN: printList(vrLb[str]);
            break;
        case LIST_STRING: printList(vrL[str]);
            break;
        }
    }
    bool needVarName = false;
    bool miss = false; // Если нужно пропустить символ

    std::string nameVar;

    const std::vector<char> strChars(str.begin(), str.end());

    if (namesOfAllVariables[str] < 60){


        for(int N = 0; N < strChars.size(); N++){
            
            // Экранизация
            if(strChars[N] == '"'){
                continue;
            }

            if(miss){
                miss = false;
                continue;
            }

            if(needVarName){
                if(strChars[N] == ' '){// Если конец имени переменной
                    printValueOfVar(namesOfAllVariables[nameVar], nameVar);
                    nameVar ="";
                    needVarName = false;
                    continue;    
                }
                nameVar += strChars[N];
                continue;
            }


            if(strChars[N] == '\\' && strChars[N+1] == '\\'){
                miss = true; // Пропуск символа дальше
                needVarName = true; // Собираем переменную
                continue;
            }
            if(strChars[N] == '\\' && strChars[N+1] == 'n'){
                miss = true; // Пропуск символа дальше
                std::cout << std::endl;
                continue;
            }
            std::cout << strChars[N];
        } 
        if (nameVar != ""){
            printValueOfVar(namesOfAllVariables[nameVar], nameVar);
        }
        if(typeOfOutput == 1) std::cout << std::endl;
    }
}

// Определяет тип переданного значения допустим "Hello"  10.5  10.78
int AutoTypeForValue(std::string valueStr){
    // Добавить переменные WORKONIT
    std::vector<char> Numerals = {'0','1','2','3','4','5','6','7','8','9','f','.'};// f для float
    std::vector<char> MathSmbls = {'^','+','-','/','*'};

    int type = _INT; // Пусть по дефолту стоит INT 

    if(valueStr == "true" || valueStr == "false"){
        return _BOOLEAN; // BOOLean
    }

    // Разбиваем строку на символы
    const std::vector<char> Chars(valueStr.begin(), valueStr.end()); 

    for(int N = 0; N < Chars.size(); N++ ){

        // Если первый символ это -, ну допусти -1 или -10.1 - это нумералы
        if (N == 0 && Chars[N] == '-'){
            continue;
        }

        // Бошка раскалывается, не хочу писать комментарии, просто не трогай тут ничего
        if (type != STRING && CheckElem(Chars[N], Numerals) == false){
            type = STRING;
        }

        if (type != STRING && Chars[N] == '.' && CheckElem(Chars[N+1], Numerals)){
            type = _FLOAT; // FLOAT я подумал double слишком жирно использовать, 
            //          так что double невозможно определить, он должен указываться в ручной типизации 
        }
        
        if( CheckElem(Chars[N], Numerals) == false && type == _INT){
            type = STRING; // String
        }
    }
    return type; // INT                  
}   

// Рефакторинг, помещает значения в переменную, нужно для оптимизации функции analyscode
void putValueToVar(std::string variableName, std::string value){
    bool valueIsVar;
    int typeOfVar = namesOfAllVariables[value];

    if (typeOfVar != 0){
        valueIsVar = true;
    }else{
        typeOfVar = AutoTypeForValue(value);
    }

    switch (typeOfVar)
    {
    
        case _INT:
            if (valueIsVar){
                vrI[variableName] = vrI[value];
            }else{
                vrI[variableName] = std::stoi(value);
            } 
            break;

        case _FLOAT:

            if (valueIsVar){
                vrF[variableName] = vrF[value];
            }else{
                vrF[variableName] = std::stof(value);
            }
            break;
        case _DOUBLE:

            if (valueIsVar){
                vrD[variableName] = vrD[value];
            }else{
                vrD[variableName] = std::stod(value);
            }                                 
            break;

        case _BOOLEAN:

            if (valueIsVar){
                vrB[variableName] = vrB[value];
            }else{
                if (value == "true"){
                    vrB[variableName] = true;
                }
                else if (value == "false"){
                    vrB[variableName] = false;
                }
            } 
            break;

        case STRING:
            if (valueIsVar){
                vrS[variableName] = vrS[value];
            }else{
                vrS[variableName] = value;
            }
            break;
    }
}

// get();
void getMethod(std::string varName){

    int typeOfVar = namesOfAllVariables[varName];

    if (typeOfVar == NON_TYPE){
        std::string *localInputForVar = new std::string;
        std::cout << varName << ": ";
        std::getline(std::cin, *localInputForVar);
        namesOfAllVariables[varName] = AutoTypeForValue(*localInputForVar);
        putValueToVar(varName, *localInputForVar);
    }

    // // Если тип не указан, то пусть это будет string
    // if(typeOfVar == 0){
    //     typeOfVar = 5;
    //     namesOfAllVariables[varName] = 5;
    // }

    if (typeOfVar == _INT){ // INT
        int *localInputForVar = new int;
        std::cout << varName << ": "; // WORKONIT убрать
        std::cin >> *localInputForVar;
        vrI[varName] = *localInputForVar;
        delete localInputForVar;
    }
    if (typeOfVar == _FLOAT){ // FLOAT
        float *localInputForVar = new float;
        std::cout << varName << ": "; // WORKONIT убрать
        std::cin >> *localInputForVar;
        vrF[varName] = *localInputForVar;
        delete localInputForVar;
    }
    if (typeOfVar == _DOUBLE){// DOUBLE
        double *localInputForVar = new double;
        std::cout << varName << ": "; // WORKONIT убрать
        std::cin >> *localInputForVar;
        vrD[varName] = *localInputForVar;
        delete localInputForVar;
    }
    if (typeOfVar == _BOOLEAN){// BOOLEAN
        std::string *localInputForVar = new std::string;
        std::cout << varName << ": "; // WORKONIT убрать
        std::cin >> *localInputForVar;
        if(*localInputForVar == "true" || *localInputForVar == "True"){
            vrB[varName] = 1;
        }
        if(*localInputForVar == "false" || *localInputForVar == "False"){
            vrB[varName] = 0;
        }
        delete localInputForVar;
    }
    if (typeOfVar == STRING){// STRING
        std::string *localInputForVar = new std::string;
        std::cout << varName << ": "; // WORKONIT убрать
        std::getline(std::cin,*localInputForVar);
        vrS[varName] = *localInputForVar;
        delete localInputForVar;    
    }

}

// typeID();
void typeID(std::string varName){
    std::cout << "The type of "<< varName << " is " << namesOfAllVariables[varName] << std::endl;
}

// sout();
void speedPrint( const std::vector<std::string> &args){

    std::string str = args[0]; // Строка
    int delay = std::stoi(args[1]); // Задержка

    // Если в качестве аргумента перемданна переменная
    if(namesOfAllVariables[str] == 5){
        str = vrS[str];
    }

    bool needVarName = false;
    bool miss = false; // Если нужно пропустить символ

    std::string nameVar;

    const std::vector<char> strChars(str.begin(), str.end());


    if(delay == 333 || delay == 222 || delay == 111){

        for(int N  = strChars.size()-1; N >= 0; N--){
            if(strChars[N] == '"') continue; // Пропускаем символ 
            std::cout << strChars[N];
            Sleep(delay);
        }
        std::cout << std::endl;
    }else{
        for(int N = 0; N < strChars.size(); N++){
            
            // Экранизация

            if(miss){
                miss = false;
                continue;
            }

            if(needVarName){
                if(strChars[N] == ' '){// Если конец имени переменной
                    // WORKONIT добавить все типы
                    printValueOfVar(namesOfAllVariables[nameVar], nameVar);
                    nameVar ="";
                    needVarName = false;
                    continue;    
                }
                nameVar += strChars[N];
                continue;
            }


            if(strChars[N] == '\\' && strChars[N+1] == '\\'){
                miss = true; // Пропуск символа дальше
                needVarName = true; // Собираем переменную
                continue;
            }
            if(strChars[N] == '\\' && strChars[N+1] == 'n'){
                miss = true; // Пропуск символа дальше
                std::cout << std::endl;
                continue;
            }
            if(strChars[N] == '"') continue; // Пропускаем символ 
            std::cout << strChars[N];
            Sleep(delay);
        }  
        std::cout << std::endl;
    }
    if (nameVar != ""){
        printValueOfVar(namesOfAllVariables[nameVar], nameVar);
    }

}

// Если сравниваются разные типы данных
void if_typeErrorThrow(){
    std::cout << "\nDamn, i really sorry for it.\nIf I could somehow remove this flaw, Im do it now. But Im just code, just parser\n";
    std::cout << "I can't do it. Sorry for wested your time.\nIm so sorry.\nBut I can help you. Let's see..";
    std::cout << "\nHmm.. seem like you try compare diffrent types.\nBe more attentive next time. Good luck. I love you ;) \n";
    std::cout << "\nNow i wanna say that 'if' return FALSE. Its not JS.." << std::endl;
}

// Слабонервным лучше не заглядывать сюда
bool if_Comparison(std::string argFirst, std::string argSecond, std::string argOfComparison, int typeOfArgs){


    // Проверяем, что за код нам отправили и возвращаем долгожданное значение
    if(typeOfArgs == _INT)
    {
        if(argOfComparison == "124"){ if(std::stoi(argFirst)/2 == std::stoi(argSecond)) return true; }
        if(argOfComparison == "120"){ if(std::stoi(argFirst) == std::stoi(argSecond)/2) return true; }
        if(argOfComparison == "94"){ if(std::stoi(argFirst) != std::stoi(argSecond)) return true; }
        if(argOfComparison == "62"){ if(std::stoi(argFirst) > std::stoi(argSecond)) return true; }
        if(argOfComparison == "60"){ if(std::stoi(argFirst) < std::stoi(argSecond)) return true; }
        if(argOfComparison == "123"){ if(std::stoi(argFirst) >= std::stoi(argSecond)) return true; }
        if(argOfComparison == "122"){ if(std::stoi(argFirst) == std::stoi(argSecond)) return true; }
        if(argOfComparison == "121"){ if(std::stoi(argFirst) <= std::stoi(argSecond)) return true; }
    }
    else if(typeOfArgs == _FLOAT)
    {
        if(argOfComparison == "124"){ if(std::stof(argFirst)/2 == std::stof(argSecond)) return true; }
        if(argOfComparison == "120"){ if(std::stof(argFirst) == std::stof(argSecond)/2) return true; }
        if(argOfComparison == "94"){ if(std::stof(argFirst) != std::stof(argSecond)) return true; }
        if(argOfComparison == "62"){ if(std::stof(argFirst) > std::stof(argSecond)) return true; }
        if(argOfComparison == "60"){ if(std::stof(argFirst) < std::stof(argSecond)) return true; }
        if(argOfComparison == "123"){ if(std::stof(argFirst) >= std::stof(argSecond)) return true; }
        if(argOfComparison == "122"){ if(std::stof(argFirst) == std::stof(argSecond)) return true; }
        if(argOfComparison == "121"){ if(std::stof(argFirst) <= std::stof(argSecond)) return true; }
    }
    else if(typeOfArgs == _DOUBLE)
    {
        if(argOfComparison == "124"){ if(std::stod(argFirst)/2 == std::stod(argSecond)) return true; }
        if(argOfComparison == "120"){ if(std::stod(argFirst) == std::stod(argSecond)/2) return true; }
        if(argOfComparison == "94"){ if(std::stod(argFirst) != std::stod(argSecond)) return true; }
        if(argOfComparison == "62"){ if(std::stod(argFirst) > std::stod(argSecond)) return true; }
        if(argOfComparison == "60"){ if(std::stod(argFirst) < std::stod(argSecond)) return true; }
        if(argOfComparison == "123"){ if(std::stod(argFirst) >= std::stod(argSecond)) return true; }
        if(argOfComparison == "122"){ if(std::stod(argFirst) == std::stod(argSecond)) return true; }
        if(argOfComparison == "121"){ if(std::stod(argFirst) <= std::stod(argSecond)) return true; }
    }
    else if(typeOfArgs == _BOOLEAN)
    {
        if(argOfComparison == "122"){ if(std::stoi(argFirst) == std::stoi(argSecond)) return true; }
    }
    else if(typeOfArgs == STRING)
    {
        if(argOfComparison == "124"){ if(argFirst.length()/2 == argSecond.length()) return true; }
        if(argOfComparison == "120"){ if(argFirst.length() == argSecond.length()/2) return true; }
        if(argOfComparison == "60"){ if(argFirst.length() != argSecond.length()) return true; }
        if(argOfComparison == "62"){ if(argFirst.length() > argSecond.length()) return true; }
        if(argOfComparison == "60"){ if(argFirst.length() < argSecond.length()) return true; }
        if(argOfComparison == "123"){ if(argFirst.length() >= argSecond.length()) return true; }
        if(argOfComparison == "122"){ if(argFirst == argSecond) return true; }
        if(argOfComparison == "121"){ if(argFirst.length() <= argSecond.length()) return true; }
    }

    return false;
}
// Пример if(num == 10)
bool if_ComparisonSupport(const std::vector<std::string> &args){

    // WORKONIT мне не нравится всё это месево с конвертацией, подумай, может можно обойтись без этого 

    int typeOfFirstArg; // Тип данных первого аргумента
    int typeOfSecondArg;// Можно уже догадаться. Я их буду сравнивать, чтобы избежать ошибок.
                        // Если типы не совпадают, то сравнение невозможно, выдается исключение
    // Сравнения
    std::string argFirst = args[0];// num из пример
    std::string argSecond = args[2];// 10, также из примера 

    // Знак сравнения
    std::string argOfComparison = args[1]; // Приходит один из кодов допустим:
                                        /*
                                            123 - "=>"
                                            122 - "=="
                                            121 - "=<"                                        
                                        */ 


    // Если аргумент1 сравнения является переменная
    if (namesOfAllVariables[argFirst] != NON_TYPE )
    {
        typeOfFirstArg = namesOfAllVariables[argFirst];

        switch (typeOfFirstArg)
        {
        case _INT: argFirst = std::to_string(vrI[argFirst]);
            break;
        case _FLOAT: argFirst = std::to_string(vrF[argFirst]);
            break;
        case _DOUBLE: argFirst = std::to_string(vrD[argFirst]);
            break;
        case _BOOLEAN: argFirst = std::to_string(vrB[argFirst]);
            break;
        case STRING: argFirst = vrS[argFirst];
            break;
        }
    }else{
        typeOfFirstArg = AutoTypeForValue(argFirst);
    }

    // Если аргумент2 сравнения является переменная
    if (namesOfAllVariables[argSecond] != NON_TYPE) 
    {
        typeOfSecondArg = namesOfAllVariables[argSecond];

        switch (typeOfSecondArg)
        {
        case _INT: argSecond = std::to_string(vrI[argSecond]);
            break;
        case _FLOAT: argSecond = std::to_string(vrF[argSecond]);
            break;
        case _DOUBLE: argSecond = std::to_string(vrD[argSecond]);
            break;
        case _BOOLEAN: argSecond = std::to_string(vrB[argSecond]);
            break;
        case STRING: argSecond = vrS[argSecond];
            break;
        }
    }else{
        typeOfSecondArg = AutoTypeForValue(argSecond); 
    }


    if(typeOfFirstArg != typeOfSecondArg) if_typeErrorThrow();

    std::string strWithout;
    
    // Если это чистая строка, то есть с ковычками, то нам нужно избавиться от них
    if(namesOfAllVariables[args[1]] == 0){
        // Избавляемся от ковычек, если тип данных строка
        if(typeOfFirstArg == STRING){

            std::vector<char> localCharsOfArgFirst(argFirst.begin(), argFirst.end());
            for(char j : localCharsOfArgFirst){
                if(j == '"'){
                    continue;
                }
                strWithout += j;
            }
            localCharsOfArgFirst.clear();

            argFirst = strWithout;
            strWithout = "";
        }
    }
    if(namesOfAllVariables[argSecond] == 0){
        if(typeOfSecondArg == STRING){

            std::vector<char> localCharsOfArgSecond(argSecond.begin(), argSecond.end());
            for(char j : localCharsOfArgSecond){
                if(j == '"'){
                    continue;
                }
                strWithout += j;
            }
            localCharsOfArgSecond.clear();

            argSecond = strWithout;
        }
    }

    return if_Comparison(argFirst, argSecond, argOfComparison, typeOfFirstArg);
}

void functionFROM(std::string var, const std::vector<std::string> &args){
    std::string list = args[0];
    int typeOfList = namesOfAllVariables[list]; 
    int typeOfVar = namesOfAllVariables[var];

    if (typeOfVar == 0){
        namesOfAllVariables[var] = typeOfList-60;
        typeOfVar = namesOfAllVariables[var];
    }

    if (typeOfVar != typeOfList-60){
        std::cout << "TypeError" << std::endl;
    }

    // Получаем значение из списка и ложим в переменную
    switch (typeOfList)
    {
    case LIST_INT: vrI[var] = vrLi[list][std::stoi(args[1])-1]; // Вызываем значение по индексу и отдаем его переменной.
        break;
    case LIST_FLOAT: vrF[var] = vrLf[list][std::stoi(args[1])-1];// -1 так как нужно создать порядочный вызов
        break;
    case LIST_DOUBLE: vrD[var] = vrLd[list][std::stoi(args[1])-1];
        break;
    case LIST_BOOLEAN: vrB[var] = vrLb[list][std::stoi(args[1])-1];
        break;
    case LIST_STRING: vrS[var] = vrL[list][std::stoi(args[1])-1]; 
        break;
    }
}
// Angel(); - это как split() на пайтоне
std::vector<std::string> Angel(const std::vector<std::string> &args){ 
    std::string localCharsOfArgs1;
    std::string str;
    // Провряем аргумент ли это переменной
    if(namesOfAllVariables[args[0]] == STRING){
        str = vrS[args[0]]; 
    }else{ str = args[0]; }
    
    char symbol;
    int indexOfCorrectReturn = 0;// Если есть запрос на мгновенное возвращение элемента обработоного этой функцией 
    int thisIndex = 0; // Нужен для запроса на возвращение элемента

    // Не хочу запариваться, потом если рефакторить буду нужно исправить, а пока так оставлю
    if(args[1] == "''" || args[1] == "34"){ 
        symbol = ' '; 
    }else{
        localCharsOfArgs1 = args[1];
        symbol = localCharsOfArgs1[0]; // Берет символ из второго аргумента.
    }
    
    if(args.size() > 2){
        indexOfCorrectReturn = std::stoi(args[2]);
    }


    std::string word;
    std::vector<std::string> result;
    std::vector<char> strChars(str.begin(), str.end());

    for(int N = 0; N < strChars.size(); N++){
        if(strChars[N] == symbol){ 
            thisIndex += 1;
            // Если нам нужно вернуть вектор с один элементом, под указанным индексом 
            if(indexOfCorrectReturn != 0){
                if(thisIndex == indexOfCorrectReturn){ break; }
            }else{// Если мы получили вектор без третьего элемента
                result.push_back(word);
            }
            word = "";
            continue; 
        }
        word += strChars[N];
    }

    result.push_back(word);
    return result;
}


void CrashScript(){
    throw -1;
}


// Функция для анализа кода и выполнения
void analysCodeKS(const std::vector<char> &chars_input){

    const std::vector<char> &chars = chars_input; // Для использования в коде.


    // Все необходимое...

    DebugMetaStatictics dbstats;


    std::string 
        lastCall,// Нужно вызвать метод или функцию
        value, // Значение переменной и не только
        func, // Определяем функцию, либо метод
        argumets,// Добавляем аргументы
        variableName;

    std::vector<std::string>
        for_comparison,
        listOfManyArguments,// Для количества аргументов    
        LocalVec = {}; // Если имеем дело с List

    // Самый главный апендикс, я честно не знаю что это,
    // но знаю, что без нее ничего не рабоатет, нужно рефакторить
    // и убирать эту хрень. Код загнуться может, пожалуйста послушай)
    int typeOfVariableChecker = 0; // 
    
    int 
        timesForRepeat = -1, // Кол-во раз выполнения определенного блока кода
        typeForVector = 0, // Тип значения для вектора
        typeForVariable = 0,
        typeOfValue = 0,
        backIndx,i; // Итераторы

    bool 
         areaOfComments = false, // Место под комментарий
         for_loop = false, // Задействован цикл  for
         repeatCode = false, // Если нужно повторить участок кода reapet
         varArgumentsCall = false, // Если вызывается метод, либо функция при объявлении переменной
         if_ReturnFalse = false, // Означает пропуск содержимого в условии
         valueIsVar = false, // если в качестве значения вызвыается переменная
         stringIsTrue = false, // если мы нашли строку
         valueAdding = false, // Нахождение значения для переменной
         variableNameAdding = false, // Если найден символ ! и объявляеться переменная
         codeStarted = false,// Если найден символ $
         functionAdding = true, // Добавление функции, либо метода
         argumetsAdding = false, // Добавление аргументов к методу, либо функции
         stringStarted = false, // если работает со строкой
         missSymbol = false; // WORKONIT убрать в будущем -- зачем?
//  ===========================================

    for(i = 0; i < chars.size(); i++)
    {
        char symbol_later = chars[i-1]; // Символ перед now
        char symbol_now = chars[i]; // Символ идущий дальше по вектору
        char symbol_next = chars[i+1]; // Символ следующий дальше

        // std::cout << func << std::endl;
        // std::cout << symbol_now << std::endl;
        
    //     // Счетчики неких штук
    //     if (stringIsTrue == false && symbol_now == ';'){
    //         dbstats.countCalls += 1;
    //     }

    //     dbstats.countSmbls += 1;

    // //-=-=-=-=-


        // Перехватка комментариев
        if (areaOfComments && symbol_now != '*'){
            continue;
        }

        if (symbol_now == START_CODE and codeStarted == false){
            codeStarted = true; // Начало анализа
            continue;
        }
        // WORKONIT нужно ли это нам?
        if(symbol_now == START_CODE and codeStarted){
            if (DebugMetaSwitch){
                std::cout << "size of chars: " << sizeof chars << std::endl;      
            }
        } 

        if (missSymbol){
            missSymbol = false;
            continue;
        }

        if (varArgumentsCall && symbol_now != ',' && symbol_now != ')') {
            if (stringIsTrue && symbol_now == '"'){ stringIsTrue = false; continue; }
            if (symbol_now == '"' && stringIsTrue == false){ stringIsTrue = true; continue; }
            if (stringIsTrue == false && symbol_now == ' '){ continue; }
            argumets += symbol_now;
            continue;
        }

        // Если выполняется цикл и находим конец его блока
        if (for_loop && symbol_now == '}'){
            // Проверяем условие цикла
            if (if_ComparisonSupport(for_comparison)){
                // Если условие верно, то воспроизводим кусок кода еще раз
                i = backIndx;
            }
        }


        // Условие вернуло false значит все содержимое мы пропускаем 
        if (if_ReturnFalse && symbol_now != '}'){
            continue;
        }else{
            if_ReturnFalse = false;
            if (symbol_now == '}'){
                continue;
            }
        }


            // ## Переменные, выделение памяти
    // =====================================================
        if(codeStarted == true){

            // Типизация     
            // Пример  ~i a;
            
            if(symbol_now == '~' && !stringIsTrue){
                functionAdding = false;
                variableNameAdding = true;
                // Определяем тип
                if (symbol_next == 'i'){// INT
                    typeForVariable = _INT;
                }
                if (symbol_next == 'f'){// FLOAT
                    typeForVariable = _FLOAT;
                }
                if (symbol_next == 'd'){// DOUBLE
                    typeForVariable = _DOUBLE;
                }
                if (symbol_next == 'b'){// BOOLEAN
                    typeForVariable = _BOOLEAN;
                }
                if (symbol_next == 's'){// STRING
                    typeForVariable = STRING;
                }
                missSymbol = true; // Для пропуска символа после тильды
                continue;
            }

            if ((symbol_now == '!' || symbol_now == '.') && (!stringIsTrue && !valueAdding)){
                functionAdding = false;
                variableNameAdding = true;
                continue;
            }
        
        // Всякого рода операции, допустим var++;
    // -       =========   ==========

            // Обработка var++;

            if (functionAdding && symbol_now == ';' && symbol_later == '+'){
                
                switch (namesOfAllVariables[func])
                {
                case _INT: vrI[func] += 1; break;
                case _FLOAT: vrF[func] += 1.0; break;
                case _DOUBLE: vrD[func] += 1.0; break;
                // SECRET JOKE
                case _BOOLEAN: vrB[func] += 1; break;
                
                default:// Исключение WORKONIT
                    break;
                }
                func = "";
                continue;
            }

            // Обработка комментариев

            if (areaOfComments && symbol_now == '*'){
                areaOfComments = false;
                continue;
            }
            

            if (functionAdding && symbol_now == '*' && !areaOfComments){
                areaOfComments = true;
                continue;
            }




            // Обнаружение типов
        //===================================================

            if (valueAdding == true)
            {
                
                if (symbol_now == ',' && stringIsTrue == false && varArgumentsCall == false){
                    
                    if (typeOfVariableChecker == STRING){ typeOfValue = STRING; }
                    // Проверка на единственнй тип
                    if (typeOfValue  != NON_TYPE && typeOfValue != AutoTypeForValue(value)){
                        std::cout << TypeError << std::endl;
                        break; // WORKONIT сделать исключение, либо перевод в другой тип данных
                    }

                    if (typeOfVariableChecker != LIST_STRING){
                        typeOfValue = AutoTypeForValue(value);
                    }           
                    

                    switch (typeOfValue)
                    {   
                        case _INT:
                            typeOfVariableChecker = LIST_INT;
                            vrLi[variableName].push_back(std::stoi(value));    
                            break;                  
                        case _FLOAT:
                            typeOfVariableChecker = LIST_FLOAT;
                            vrLf[variableName].push_back(std::stof(value));
                            break;
                        case _DOUBLE: 
                            typeOfVariableChecker = LIST_DOUBLE;
                            vrLd[variableName].push_back(std::stod(value));
                            break;
                        case _BOOLEAN:
                            typeOfVariableChecker = LIST_BOOLEAN;
                            if (value == "true"){
                                vrLb[variableName].push_back(true);
                            }
                            if (value == "false"){
                                vrLb[variableName].push_back(false);
                            }
                            break;
                        case STRING:
                            typeOfVariableChecker = LIST_STRING;
                            vrL[variableName].push_back(value);

                    }
 
                    value ="";
                    continue;
                    
                }
                    
                //===============================================

                if (symbol_now == '"' && !stringIsTrue){
                    typeOfVariableChecker = STRING;
                    stringIsTrue = true;
                    continue;
                }

                if (stringIsTrue){        
                         
                    if(symbol_now == '"'){
                        stringIsTrue = false;
                        continue;
                    }
                    value += symbol_now;
                    continue;    
                }
                
                //==============================================
                
            // Конец строки !num = 10; <-- Мы щяс прямо на последнем символе.
            
                if (stringIsTrue == false and symbol_now == ';'){ // если ; не относиться к строке, то

                    // Пора уже добавить переменную
                    if (value != ""){

                        // Если значение это имя переменной
                        if (namesOfAllVariables[value] != NON_TYPE){
                            typeOfVariableChecker = namesOfAllVariables[value];
                            valueIsVar = true;
                        }else{
                            if (typeOfVariableChecker == NON_TYPE){
                                typeOfVariableChecker = AutoTypeForValue(value);
                            }
                        }
                        // love only one
                        if (variableName == "love"){
                            if (value != "1" && value != "0"){
                                std::cout << "ER:: var 'love' can not have value like that. Valid values: 1,0" << std::endl;
                                std::cout << "love only one!" << std::endl;
                            }
                        }

                        // Нужно в отдельную функцию вынести, провести рефакторинг
                        switch (typeOfVariableChecker)
                        {
                            case LIST_INT: vrLi[variableName].push_back(std::stoi(value)); break;                  
                            case LIST_FLOAT: vrLf[variableName].push_back(std::stof(value)); break;
                            case LIST_DOUBLE: vrLd[variableName].push_back(std::stod(value)); break;
                            case LIST_BOOLEAN: vrLb[variableName].push_back(std::stoi(value)); break;
                            case LIST_STRING: vrL[variableName].push_back(value);        

                            default:
                                putValueToVar(variableName, value);

                        }   
                        

                        // Если переменная не существует, то добаляем ее.
                        if(namesOfAllVariables[variableName] == NON_TYPE)
                            namesOfAllVariables[variableName]  = typeOfVariableChecker;

                    }
                    
                    typeOfValue = NON_TYPE;
                    typeOfVariableChecker = 0;
                    value = "";
                    variableName = "";
                    LocalVec = {};
                    

                    stringIsTrue = false; 
                    valueAdding = false; 
                    variableNameAdding = false; 
                    functionAdding = true; 
                    argumetsAdding = false; 
                    stringStarted = false;

                    continue;
                }

            // Если в переменной вызывается функция

                if (varArgumentsCall)
                {
                    if (symbol_now == ','){ listOfManyArguments.push_back(argumets); argumets = ""; }

                    if (symbol_now == ')')
                    {
                        varArgumentsCall = false;
            
                        // Добавляем последний аргумент
                        listOfManyArguments.push_back(argumets);
                        argumets = "";

                        // from();
                        if (lastCall == LIST_FROM){
                            // Скармливаем все данные из строки
                            functionFROM(variableName, listOfManyArguments);
                        }
                        
                        // angela();
                        if (lastCall == ANGEL_FUNCTION){
                            // Запрос на возвращение элемента
                            
                            if (listOfManyArguments.size() > 2){
                                namesOfAllVariables[variableName] = STRING;
                                vrS[variableName] = Angel(listOfManyArguments)[0];
                            }else{// Если возвращает просто вектор
                                namesOfAllVariables[variableName] = LIST_STRING; // Так как angela(); возвращает вектор строк
                                vrL[variableName] = Angel(listOfManyArguments);
                            }
                        }
                        
                        listOfManyArguments.clear();
                        continue;
                    }

                }

                if (symbol_now == '(' && !stringIsTrue){
                    varArgumentsCall = true; 
                    lastCall = value;
                    value = "";
                    continue;
                } 

            // Добавление значения

                if (symbol_now != ';' && symbol_now != ' ' && varArgumentsCall == false){
                    value += symbol_now;
                }

                
            }

            
            // Имя переменной
            if (variableNameAdding == true)
            {
                // WORKONIT предпосылки  к пиздецу в структкре кода -- работает - не трогай
                // Я без понятия что это
                if (chars[i-1] != ')' && symbol_now == ';'){
                    variableNameAdding = false;
                    functionAdding = true;
                    namesOfAllVariables.emplace(variableName, typeForVariable);
                    variableName = "";
                    continue;
                }

                if (symbol_now == '='){
                    //  !num = 10; если мы находим = то теперь добавляем значение
                    variableNameAdding = false;
                    valueAdding = true;
                    continue;   
                }
                if (symbol_now != ' '){
                    variableName += symbol_now;
                }       
                
                
            }
 //        Repeat
    
    //          Repeat

            // code style
            if (repeatCode && func == ">"){
                backIndx = i+1;
                func = "";
            }

            if (symbol_now == POINT_SYN_CHAR && functionAdding && repeatCode == false){
                backIndx = i+1;
                repeatCode = true;
                continue; // Пропускаем ':'
            }
            // Объясняю. У нас всегда собирается func, а значит     
            // мы можем воспользоваться этим, ну то есть кол-во раз выполнения уже лежит в func
            // в общем, DB тебе в помощь, я объяснил как мог.
            if (repeatCode && symbol_now == POINT_SYN_CHAR){
                if (timesForRepeat == -1){
                    if (namesOfAllVariables[func] == NON_TYPE){
                        timesForRepeat = std::stoi(func);
                    }else{
                        if (namesOfAllVariables[func] != _INT){
                            // WORKONIT исключение
                            std::cout << "WORKONIT" << std::endl;
                        }else{
                            timesForRepeat = vrI[func];
                        }
                    }
                }
                timesForRepeat -= 1;
                // Если задача выполнена
                if (timesForRepeat == 0){
                    repeatCode = false;
                    timesForRepeat = -1;                         
                }else{
                    i = backIndx;// Возвращаем цикл на метку, ну изменяем итерацию
                }
                functionAdding = true;
                func = "";
                continue;
            }
            
// =====================================================================================================================

            // ## Функции и методы, аргументы, условия
            

                //                  Упоминание для условий
            if (symbol_now == ';' || symbol_now == '{' && argumetsAdding == false && functionAdding == false){

            // Ветвление    
                if (lastCall == IF_SYN){
                    // Скармлеваем функции те аргументы, что удалось найти, если вернуло false, то скипаем все, что в условии
                    if(if_ComparisonSupport(listOfManyArguments) == true){
                        if_ReturnFalse = false;
                    }
                    else{ if_ReturnFalse = true; } 
                }
            
            // Методы с 2мя аргументами
                
                if (amountOfArgumentsForEachMethod[lastCall] == 2)
                {
                    // sout();
                    if (lastCall == SPEED_PRINT){
                        speedPrint(listOfManyArguments);
                    }
                }

            // For

                if  (lastCall == FOR_SYN){
                    for_comparison = listOfManyArguments; // Перекидываем аргументы, в специальный список для for()
                    for_loop = true;
                    backIndx = i+1;   
                } 


            //============

            // Методы с поддержкой только одного аргумента

                // GET()
                if (lastCall == INPUT_METHOD){
                    getMethod(argumets);
                }
                // typeID();
                if (lastCall == DB_METHOD_ID){
                    typeID(argumets);
                }               
                // OUT()  &   LOUT()
                if (lastCall == OUTPUT_METHOD){
                    OutputMethod(argumets, 0);
                }else if (lastCall == OUTPUT_METHOD_ENTER){
                    OutputMethod(argumets, 1);
                }   
                if (lastCall == STOP_SCRIPT){
                    // Нужно правильно вывести строку
                    OutputMethod(argumets, 1);
                    break;
                }         
                if (lastCall == CRASH_SCRIPT){
                    CrashScript();
                }   
            //===================
                listOfManyArguments.clear();
                functionAdding = true;
                argumets = "";
                lastCall = "";
                continue;
            }

            if (argumetsAdding){
                // Символы для определения сравнения - это именно второй символ после '=':  =>,  =<,  ==. 
                const std::vector<char> charsForIfComparison = {'=','>','<','!'};
                // Если использованнно ветвление if(num == 10){} и for(a < 10){}
                if (lastCall == IF_SYN || lastCall == FOR_SYN){
                    if (CheckElem(symbol_now, charsForIfComparison) && !stringIsTrue ){
                        listOfManyArguments.push_back(argumets); // Добавляем num из примера выше
                        argumets = "";
                        // Если после = следует еще один знак сравнения
                        if (CheckElem(symbol_next, charsForIfComparison))
                        {
                            // Складываем 2 символа, значит получаем int, по нему мы и ориентируемся дальше, подробнее в функции if_ComparisonSupport
                            listOfManyArguments.push_back(std::to_string(symbol_now + symbol_next));                                                                                    
                            missSymbol = true; // Избаляемся от "==" допустим
                            continue; // Избаляемся от "==" допустим
                        
                        }else{
                            listOfManyArguments.push_back(std::to_string((int) symbol_now));
                            continue;
                        }
                    }                  
                }
                // Определение строки, чтобы избежать курьеза в проверках на символы
                if (stringIsTrue && symbol_now == '"'){
                    stringIsTrue = false;
                }

                if (!stringIsTrue && symbol_now == '"'){
                    stringIsTrue = true;
                }
                // Если введенны несколько аргументов sout("Hello", 300);
                if (symbol_now == ',' && !stringIsTrue){
                    // Добавляем один из введенных аргументов
                    listOfManyArguments.push_back(argumets);
                    argumets = ""; // Нашли аргумент, добавили, переходим к следующему
                    continue;
                }
                // Конец аргументов
                if (symbol_now == ')'){
                    stringIsTrue = false;
                    // Если есть другие аргументы, то нужно добавить последний
                    if(listOfManyArguments.size() > 0) listOfManyArguments.push_back(argumets);

                    argumetsAdding = false;
                    continue; // Пропускаем скобку
                }
                if (symbol_now == ' ' && !stringIsTrue)
                    continue;
                else
                    argumets += symbol_now;
            }

            if (functionAdding && symbol_now == '(')
            {
                lastCall = func;
                func = "";
                functionAdding = false;
                argumetsAdding = true;
                continue;  // Пропускаем скобку
            }

            if (functionAdding){
                if(symbol_now == ' ' || symbol_now == '+' || symbol_now == '-') continue;
                func += symbol_now;
            }
        }

    }
    // preStart(); // Без понятия что это
}   

void readFile(std::string FileName){

    //WORKONIT 
    /* 
    Имя файла может указываться полностью. Пока будет так, 
    что он проверяет на наличие файла в своей директории и сразу же его открывает
    если он один. Если нет, то спрашивает пользователя, если  нет в папке, то просит
    указать имя полностью.
    */
    // Meta.ks
    std::regex set_file_name("([\\w-]+)" // Meta - название
                             "(\\.)" // . - Файл ли это.
                             "(ks)"// ks - расширение KS
                            );
    std::cmatch result;

    // Если файл соответсвует требованиям
    if(std::regex_match(FileName.c_str(), result ,set_file_name )){
        std::cout << "File is valid" << std::endl;
    }else{
        std::cout << "| - 1 | File is not valid" << std::endl;
    }

    std::vector<char> *timeArrayOfChar = new std::vector<char>; 

    std::vector<char> *charArrayOfCode = new std::vector<char>;

    std::vector<std::string> *filesStrings = new std::vector<std::string>;

    std::string line;
 
    std::ifstream loc_file(FileName); // окрываем файл для чтения, loc_file - объект класса
    if (loc_file.is_open()){

        while (getline(loc_file, line))
        {
            filesStrings -> push_back(line); // добавление строки 
        }
    }else{
        std::cout<< "-1";
        return;
    }
    loc_file.close();     // закрываем файл
    
    // std::cout << files_strings -> size() << std::endl; <DB>

    for(int i = 0; i < filesStrings -> size(); i++){

        const int len = (*filesStrings)[i].length();
        char charArrayOfCode[len+1];
 
        // Копируем содержимое строки и переводим в массив
        std::strcpy(charArrayOfCode, (*filesStrings)[i].c_str());
        for (int i = 0; i < len; i++)
            timeArrayOfChar -> push_back(charArrayOfCode[i]);
    
    }
    // array_of_char изминяться не будет, так что ее спокойно можно делать константой
    const std::vector<char> arrayOfChar[timeArrayOfChar  -> size()]  = *timeArrayOfChar;

// Очитка памяти. Мы не знаем сколько строк будет в файле .ks и оставлять их я не вижу смысла.
    charArrayOfCode -> clear();
    delete charArrayOfCode;

    filesStrings -> clear();
    delete filesStrings;

    timeArrayOfChar -> clear();
    delete timeArrayOfChar;
// =================================================

    analysCodeKS(*arrayOfChar);
    // Если строки закончились, переходим к анализу
}

int main(){
    // -- HARDCODED
    readFile("Meta.ks"); // чтение файла
    // std::cout << AutoTypeForValue("10.1");
    system("pause>nul");
}
