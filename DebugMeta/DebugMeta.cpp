
// Проверить все ли норм работает 

#include <map> // словари
#include <iostream>
#include <fstream> // Работа с файлами
#include <string>
#include <vector>
#include <cstring> // Для разбивание строк/копирования на символы, методы strcpy и c_str
#include <regex> // Регулярки
#include <windows.h> // Жалуется антивирус

#define MATH_EXPRESSION 6
#define EXTRA_SYN_FOR "f_" // -- Для удобного синтаксиса 

#define START_OF_COMMENTS '*'
#define EMPTY ""
#define END_OF_LINE ';'
#define TAKE_SPACE '!'


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
const std::string FACTORIAL = "factorial";
const std::string ADD = "add";
const std::string REMOVE = "rem";
const std::string BUBBLE_SORT = "bbl_sort";
const std::string FUNC_WARN = "void";

//Словари по переменные
//==========================================================================
 // Словарь под переменные типа STRING
    std::map <std::string, std::string> _vrS;
 // Словарь под переменные типа INTEGER
    std::map <std::string, int> _vrI;
 // Словарь под переменные типа DOUBLE WORKONIT пока под вопросом
    std::map <std::string, double> _vrD;
 // Словарь под переменные типа BOOLEAN
    std::map <std::string, bool> _vrB;
 // Словарь под переменные типа FLOAT WORKONIT пока под вопросом
    std::map <std::string, float> _vrF;
 // Словарь под списки
    std::map <std::string, std::vector<int>> _vrLi;// LIST INT
    std::map <std::string, std::vector<float>> _vrLf;// LIST FLOAT
    std::map <std::string, std::vector<double>> _vrLd;// LIST DOUBLE
    std::map <std::string, std::vector<bool>> _vrLb;// LIST BOOLEAN
    std::map <std::string, std::vector<std::string>> _vrL;// LIST STRING


// Пара: название переменной и тип данных
std::map<std::string, int> _namesOfAllVariables;
// Функции
std::map<std::string, int> ins_Voids;
// -- Зачем это ?
std::map<std::string, int> amountOfArgumentsForEachMethod = 
{
    {REMOVE, 2},
    {ADD, 2},
    {SPEED_PRINT, 2}, // sout("hello world!", 300); <- строка и дальше задержка перед выводом.
};
// Исключения
// std::map<int, std::string>  ERR;


class AniolScriptAbilityes{

    private:
        // Пузырька
        void _bbl_sort_alg(auto &list){
            int i,j;
            int *temp = new int;

            for(i = 0; i < list.size(); i++ ){
                for(j = i+1; j < list.size(); j++ ){
                    if(list[i] > list[j]){
                        *temp = list[i];
                        list[i] = list[j];
                        list[j] = *temp;
                    }
                }
            }
            delete temp;
        }
        void _printList(const std::vector<auto> &Vec){
            for(int N = 0; N < Vec.size(); N++){
                if(Vec.size() == N+1){
                    std::cout << Vec[N];
                }else{
                    std::cout <<  Vec[N] << ",";
                }  
            }
        }
        void _printValueOfVar(int typeOfVar, std::string nameVar){
            switch (typeOfVar)
            {
                case _INT:
                    std::cout << _vrI[nameVar];
                    break;
                case _FLOAT:
                    std::cout << _vrF[nameVar];
                    break;
                case _DOUBLE:
                    std::cout << _vrD[nameVar];
                    break;    
                case _BOOLEAN:
                    std::cout << _vrB[nameVar];
                    break;    
                case STRING:
                    std::cout << _vrS[nameVar];
                    break;    
                case LIST:
                    _printList(_vrL[nameVar]);      
                    break;
                case LIST_INT:
                    _printList(_vrLi[nameVar]);
                    break;
                case LIST_FLOAT:
                    _printList(_vrLf[nameVar]);
                    break;
                case LIST_DOUBLE:
                    _printList(_vrLd[nameVar]);
                    break;
                case LIST_BOOLEAN:
                    _printList(_vrLb[nameVar]);
                    break;      
            }
        }
        // WORKONIT зачем это нужно? -- убрать
        void if_typeErrorThrow(){
            std::cout << "WORKONIT" << std::endl;
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

    public:
        void WorkVoid(const std::string &NAME_F, INT INDX){
            ins_Voids.emplace(NAME_F, INDX);
        }

        void bbl_sort(std::string& list_name){
            switch (_namesOfAllVariables[list_name])
            {
            case LIST_INT: _bbl_sort_alg(_vrLi[list_name]);
                break;
            case LIST_FLOAT: _bbl_sort_alg(_vrLf[list_name]);
                break;
            case LIST_DOUBLE: _bbl_sort_alg(_vrLd[list_name]);
                break;
                                
            }
        }
    // remove(list, value);
        // Исключение элемента из списка
        void remove(const std::vector<std::string> &args){
            int indx; 
            indx = (_namesOfAllVariables[args[1]] != 0)?_vrI[args[1]]-1 : std::stoi(args[1])-1; 
             
            switch (_namesOfAllVariables[args[0]])
                {
                case LIST_INT: _vrLi[args[0]].erase( _vrLi[args[0]].begin() + indx) ; 
                    break;
                case LIST_FLOAT: _vrLf[args[0]].erase( _vrLf[args[0]].begin() + indx) ;
                    break;
                case LIST_DOUBLE: _vrLd[args[0]].erase( _vrLd[args[0]].begin() + indx) ;
                    break;
                // WORKONIT -- true false
                case LIST_STRING: _vrL[args[0]].erase( _vrL[args[0]].begin() + indx) ;
                    break;
                
                default: // WORKONIT исключение
                    break;
                }
        }
    // add(list, value);
        // Добаление элемента в список.
        void add(const std::vector<std::string> &args){
            // Если значение это переменная
            if (_namesOfAllVariables[args[1]] != 0){
                switch (_namesOfAllVariables[args[1]])
                {
                case _INT: _vrLi[args[0]].push_back(_vrI[args[1]]);
                    break;
                case _FLOAT: _vrLf[args[0]].push_back(_vrF[args[1]]);
                    break;
                case _DOUBLE: _vrLd[args[0]].push_back(_vrD[args[1]]);
                    break;
                case _BOOLEAN: _vrLb[args[0]].push_back(_vrB[args[1]]);
                    break;
                case STRING: _vrL[args[0]].push_back(_vrS[args[1]]);
                    break;
                }
                return;
            }

        switch (_namesOfAllVariables[args[0]])
            {
            case LIST_INT: _vrLi[args[0]].push_back(std::stoi(args[1]));
                break;
            case LIST_FLOAT: _vrLf[args[0]].push_back(std::stof(args[1]));
                break;
            case LIST_DOUBLE: _vrLd[args[0]].push_back(std::stod(args[1]));
                break;
            // WORKONIT -- true false
            // case LIST_BOOLEAN: _vrLb[args[0]].push_back(std::stoi(args[1]));
            //     break;
            case LIST_STRING: _vrL[args[0]].push_back(args[1]);
                break;
            
            default: // WORKONIT исключение -- Что это?
                break;
            }
        }
        /* По рофлу решил добавить, пусть будет */
        int factorial(const std::vector<std::string> &args){
            int i,n,result;

            switch (_namesOfAllVariables[args[0]])
            {
            case _INT: n = _vrI[args[0]];
                break;
            case _FLOAT: n = _vrF[args[0]];
                break;
            case _DOUBLE: n = _vrD[args[0]];
                break;
            default:
                n = std::stoi(args[0]);
            }            
            
            i = 1, result = 1;
            // Через цикл будет быстрее и проще, так что будем юзать его.
            for(; i < n+1; i++){  
                result *= i; 
            }   
            return result;
        }
        // Проверяем есть ли символ в векторе символов
        bool CheckElem(char NeedToFind, const std::vector<char> &List){
            for(int num = 0; num < List.size(); num++){
                if(List[num] == NeedToFind){
                    return true;
                }
            }
            return false;
        }
        /*Для DB*/
        void writevec(std::vector<auto> vec){
            for(int elem = 0; elem < vec.size(); elem++){
                std::cout << elem << " . " <<  vec[elem] << " | ";  
            }
            std::cout << std::endl;
        }
        /* Вывод в консоль */
        void OutputMethod(std::string str, int typeOfOutput)
        {
            // Если аргумент - это переменная
            if(_namesOfAllVariables[str] != 0){
                switch (_namesOfAllVariables[str])
                {
                case _INT: str = std::to_string(_vrI[str]); // INT
                    break;
                case _FLOAT: str = std::to_string(_vrF[str]); // FLOAT
                    break;
                case _DOUBLE: str = std::to_string(_vrD[str]); // DOUBLE
                    break;
                case _BOOLEAN: str = std::to_string(_vrB[str]); // BOOLEAN
                    break;
                case STRING: str = _vrS[str]; // String
                    break; 
                case LIST_INT: _printList(_vrLi[str]);
                    break;
                case LIST_FLOAT: _printList(_vrLf[str]);
                    break;        
                case LIST_DOUBLE: _printList(_vrLd[str]);
                    break;
                case LIST_BOOLEAN: _printList(_vrLb[str]);
                    break;
                case LIST_STRING: _printList(_vrL[str]);
                    break;
                }
            }
            bool needVarName = false;
            bool miss = false; // Если нужно пропустить символ

            std::string nameVar;

            const std::vector<char> strChars(str.begin(), str.end());

            if (_namesOfAllVariables[str] < 60){


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
                            _printValueOfVar(_namesOfAllVariables[nameVar], nameVar);
                            nameVar = EMPTY;
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
                if (nameVar != EMPTY){
                    _printValueOfVar(_namesOfAllVariables[nameVar], nameVar);
                }
            }
            if(typeOfOutput == 1) std::cout << std::endl;
        }
        // Определяет тип переданного значения допустим "Hello"  10.5  10.78
        int AutoTypeForValue(std::string valueStr){
            // Добавить переменные WORKONIT
            const std::vector<char> Numerals  = {'0','1','2','3','4','5','6','7','8','9','f','.','('};// f для float
            const std::vector<char> MathSmbls  = {'^','+','-','/','*'};

            int type = _INT; // Пусть по дефолту стоит INT 

            if(valueStr == "true" || valueStr == "false"){
                return _BOOLEAN; // BOOLean
            }

            // Разбиваем строку на символы
            const std::vector<char> Chars(valueStr.begin(), valueStr.end()); 

            for(int N = 0; N < Chars.size(); N++ ){
                
                if (CheckElem( Chars[N], MathSmbls ) && CheckElem(Chars[N+1], Numerals) 
                    && CheckElem(Chars[N-1], Numerals) )
                    {
                        return MATH_EXPRESSION;
                }

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
            int typeOfVar = _namesOfAllVariables[value];

            if (typeOfVar != 0){
                valueIsVar = true;
            }else{
                typeOfVar = AutoTypeForValue(value);
                _namesOfAllVariables[variableName] = typeOfVar;
            }
            
            switch (typeOfVar)
            {
            
                case _INT:
                    if (valueIsVar){
                        _vrI[variableName] = _vrI[value];
                    }else{
                        _vrI[variableName] = std::stoi(value);
                    } 
                    break;

                case _FLOAT:

                    if (valueIsVar){
                        _vrF[variableName] = _vrF[value];
                    }else{
                        _vrF[variableName] = std::stof(value);
                    }
                    break;
                case _DOUBLE:

                    if (valueIsVar){
                        _vrD[variableName] = _vrD[value];
                    }else{
                        _vrD[variableName] = std::stod(value);
                    }                                 
                    break;

                case _BOOLEAN:

                    if (valueIsVar){
                        _vrB[variableName] = _vrB[value];
                    }else{
                        if (value == "true"){
                            _vrB[variableName] = true;
                        }
                        else if (value == "false"){
                            _vrB[variableName] = false;
                        }
                    } 
                    break;

                case STRING:
                    if (valueIsVar){
                        _vrS[variableName] = _vrS[value];
                    }else{
                        _vrS[variableName] = value;
                    }
                    break;
            }
        }       
        // get();
        void getMethod(std::string varName){

            int typeOfVar = _namesOfAllVariables[varName];

            if (typeOfVar == NON_TYPE){
                std::string *localInputForVar = new std::string;
                std::cout << varName << ": ";
                std::getline(std::cin, *localInputForVar);
                _namesOfAllVariables[varName] = AutoTypeForValue(*localInputForVar);
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
                _vrI[varName] = *localInputForVar;
                delete localInputForVar;
            }
            if (typeOfVar == _FLOAT){ // FLOAT
                float *localInputForVar = new float;
                std::cout << varName << ": "; // WORKONIT убрать
                std::cin >> *localInputForVar;
                _vrF[varName] = *localInputForVar;
                delete localInputForVar;
            }
            if (typeOfVar == _DOUBLE){// DOUBLE
                double *localInputForVar = new double;
                std::cout << varName << ": "; // WORKONIT убрать
                std::cin >> *localInputForVar;
                _vrD[varName] = *localInputForVar;
                delete localInputForVar;
            }
            if (typeOfVar == _BOOLEAN){// BOOLEAN
                std::string *localInputForVar = new std::string;
                std::cout << varName << ": "; // WORKONIT убрать
                std::cin >> *localInputForVar;
                if(*localInputForVar == "true" || *localInputForVar == "True"){
                    _vrB[varName] = 1;
                }
                if(*localInputForVar == "false" || *localInputForVar == "False"){
                    _vrB[varName] = 0;
                }
                delete localInputForVar;
            }
            if (typeOfVar == STRING){// STRING
                std::string *localInputForVar = new std::string;
                std::cout << varName << ": "; // WORKONIT убрать
                std::getline(std::cin,*localInputForVar);
                _vrS[varName] = *localInputForVar;
                delete localInputForVar;    
            }

        }       
        // typeID();
        void typeID(std::string varName){
            std::cout << "The type of "<< varName << " is " << _namesOfAllVariables[varName] << std::endl;
        }        
        // sout();
        void speedPrint( const std::vector<std::string> &args){
            std::string str = args[0]; // Строка
            int delay = std::stoi(args[1]); // Задержка
            
            // Если в качестве аргумента перемданна переменная
            if(_namesOfAllVariables[str] == 5){
                str = _vrS[str];
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
                            _printValueOfVar(_namesOfAllVariables[nameVar], nameVar);
                            nameVar = EMPTY;
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
            if (nameVar != EMPTY){
                _printValueOfVar(_namesOfAllVariables[nameVar], nameVar);
            }

        }      
        /* Разбевает условнность по фактам. */
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
            if (_namesOfAllVariables[argFirst] != NON_TYPE )
            {
                typeOfFirstArg = _namesOfAllVariables[argFirst];

                switch (typeOfFirstArg)
                {
                case _INT: argFirst = std::to_string(_vrI[argFirst]);
                    break;
                case _FLOAT: argFirst = std::to_string(_vrF[argFirst]);
                    break;
                case _DOUBLE: argFirst = std::to_string(_vrD[argFirst]);
                    break;
                case _BOOLEAN: argFirst = std::to_string(_vrB[argFirst]);
                    break;
                case STRING: argFirst = _vrS[argFirst];
                    break;
                }
            }else{
                typeOfFirstArg = AutoTypeForValue(argFirst);
            }

            // Если аргумент2 сравнения является переменная
            if (_namesOfAllVariables[argSecond] != NON_TYPE) 
            {
                typeOfSecondArg = _namesOfAllVariables[argSecond];

                switch (typeOfSecondArg)
                {
                case _INT: argSecond = std::to_string(_vrI[argSecond]);
                    break;
                case _FLOAT: argSecond = std::to_string(_vrF[argSecond]);
                    break;
                case _DOUBLE: argSecond = std::to_string(_vrD[argSecond]);
                    break;
                case _BOOLEAN: argSecond = std::to_string(_vrB[argSecond]);
                    break;
                case STRING: argSecond = _vrS[argSecond];
                    break;
                }
            }else{
                typeOfSecondArg = AutoTypeForValue(argSecond); 
            }


            if(typeOfFirstArg != typeOfSecondArg) if_typeErrorThrow();

            std::string strWithout;
            
            // Если это чистая строка, то есть с ковычками, то нам нужно избавиться от них
            if(_namesOfAllVariables[args[1]] == 0){
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
                    strWithout = EMPTY;
                }
            }
            if(_namesOfAllVariables[argSecond] == 0){
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
        /* Присваивание значения из списка переменной  !a = from(nums, 2); */
        void functionFROM(std::string var, const std::vector<std::string> &args){
            std::string list = args[0];
            int typeOfList = _namesOfAllVariables[list]; 
            int typeOfVar = _namesOfAllVariables[var];

            if (typeOfVar == 0){
                _namesOfAllVariables[var] = typeOfList-60;
                typeOfVar = _namesOfAllVariables[var];
            }

            if (typeOfVar != typeOfList-60){
                std::cout << "TypeError" << std::endl;
            }
            

            // Получаем значение из списка и ложим в переменную
            switch (typeOfList)
            {
            case LIST_INT: _vrI[var] = _vrLi[list][std::stoi(args[1])-1]; // Вызываем значение по индексу и отдаем его переменной.
                break;
            case LIST_FLOAT: _vrF[var] = _vrLf[list][std::stoi(args[1])-1];// -1 так как нужно создать порядочный вызов
                break;
            case LIST_DOUBLE: _vrD[var] = _vrLd[list][std::stoi(args[1])-1];
                break;
            case LIST_BOOLEAN: _vrB[var] = _vrLb[list][std::stoi(args[1])-1];
                break;
            case LIST_STRING: _vrS[var] = _vrL[list][std::stoi(args[1])-1]; 
                break;
            }
        }
        /* angela(str, ' ', 1); - это как split() на пайтоне 
        str -> строка
        ' ' -> символ, его можно указывать без ковычек. Исключение: < space >. 
        1 -> возвращение элемента (необезательно) 
        */
        std::vector<std::string> Angel(const std::vector<std::string> &args)
        {             
            std::string localCharsOfArgs1;
            std::string str;
            // Провряем аргумент ли это переменной
            str = (_namesOfAllVariables[args[0]] == STRING)?_vrS[args[0]]:args[0];
            
            char symbol;
            int indexOfCorrectReturn = 0;// Если есть запрос на мгновенное возвращение элемента обработоного этой функцией 
            int thisIndex = 0; // Нужен для запроса на возвращение элемента

            // Не хочу запариваться, потом если рефакторить буду нужно исправить, а пока так оставлю
            if(args[1] == "''" || args[1] == "32"){ 
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
                    word = EMPTY;
                    continue; 
                }
                word += strChars[N];
            }

            result.push_back(word);
            return result;
        }
        /* Краш кода  cr(); */
        void CrashScript(){
            throw -1;
        }

};

class AniolScriptParserCode: public AniolScriptAbilityes
{
private:

    // Все необходимое...

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
        void_backIndx,
        loop_backIndx,
        repeat_backIndx,i; // Итераторы

    bool 
         void_do = false,
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
         missSymbol = false, // WORKONIT убрать в будущем -- зачем?
         skipFuncBlock = false; // Пропускаем блок функции при объявлении
//  ===========================================
    void _incrementM(const std::string &VAR){
        switch (_namesOfAllVariables[VAR])
        {
        case _INT: _vrI[VAR] -= 1; break;
        case _FLOAT: _vrF[VAR] -= 1.0; break;
        case _DOUBLE: _vrD[VAR] -= 1.0; break;
        // SECRET JOKE
        case _BOOLEAN: _vrB[VAR] -= 1; break;
        
        default:// Исключение WORKONIT
            break;
        }
    }
    void _incrementP(const std::string &VAR){
        switch (_namesOfAllVariables[VAR])
        {
        case _INT: _vrI[VAR] += 1; break;
        case _FLOAT: _vrF[VAR] += 1.0; break;
        case _DOUBLE: _vrD[VAR] += 1.0; break;
        // SECRET JOKE
        case _BOOLEAN: _vrB[VAR] += 1; break;
        
        default:// Исключение WORKONIT
            break;
        }
    }
    void _addToList(const INT &TYPE_, const std::string &value){
        
        switch (TYPE_)
        {   
            case _INT:
                typeOfVariableChecker = LIST_INT;
                _vrLi[variableName].push_back(std::stoi(value));    
                break;                  
            case _FLOAT:
                typeOfVariableChecker = LIST_FLOAT;
                _vrLf[variableName].push_back(std::stof(value));
                break;
            case _DOUBLE: 
                typeOfVariableChecker = LIST_DOUBLE;
                _vrLd[variableName].push_back(std::stod(value));
                break;
            case _BOOLEAN:
                typeOfVariableChecker = LIST_BOOLEAN;
                if (value == "true"){
                    _vrLb[variableName].push_back(true);
                }
                if (value == "false"){
                    _vrLb[variableName].push_back(false);
                }
                break;
            case STRING:
                typeOfVariableChecker = LIST_STRING;
                _vrL[variableName].push_back(value);

        }
    }
    void _putValueToVar(){
        if (value != EMPTY){

            // Если значение это имя переменной
            if (_namesOfAllVariables[value] != NON_TYPE){
                typeOfVariableChecker = _namesOfAllVariables[value];
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
                case LIST_INT: _vrLi[variableName].push_back(std::stoi(value)); break;                  
                case LIST_FLOAT: _vrLf[variableName].push_back(std::stof(value)); break;
                case LIST_DOUBLE: _vrLd[variableName].push_back(std::stod(value)); break;
                case LIST_BOOLEAN: _vrLb[variableName].push_back(std::stoi(value)); break;
                case LIST_STRING: _vrL[variableName].push_back(value);        

                default:
                    putValueToVar(variableName, value);

            }   
            

            // Если переменная не существует, то добаляем ее.
            if(_namesOfAllVariables[variableName] == NON_TYPE)
                _namesOfAllVariables[variableName]  = typeOfVariableChecker;

        }        
    }
    void _getType(CHAR &symbol_next){
        // Определяем тип
        if (symbol_next == 'i'){// INT
            typeForVariable = _INT;
        }
        else if (symbol_next == 'f'){// FLOAT
            typeForVariable = _FLOAT;
        }
        else if (symbol_next == 'd'){// DOUBLE
            typeForVariable = _DOUBLE;
        }
        else  if (symbol_next == 'b'){// BOOLEAN
            typeForVariable = _BOOLEAN;
        }
        else if (symbol_next == 's'){// STRING
            typeForVariable = STRING;
        }
        else if (symbol_next == 'I'){ // LIST_INT
            typeForVariable = LIST_INT;
        }
        else if (symbol_next == 'F'){ // LIST_FLOAT
            typeForVariable = LIST_FLOAT;
        }
        else if (symbol_next == 'D'){ // LIST_DOUBLE
            typeForVariable = LIST_DOUBLE;
        }
        else if (symbol_next == 'S'){ // LIST_STRING
            typeForVariable = LIST_STRING;
        }
    }

    void _rebornSettings(){

            lastCall = EMPTY;
            value = EMPTY;
            func = EMPTY;
            argumets = EMPTY;
            variableName = EMPTY;
            
            for_comparison = {};
            listOfManyArguments = {};
            LocalVec = {}; 

            typeOfVariableChecker = 0;
            timesForRepeat = -1;
            typeForVector = 0;
            typeForVariable = 0;
            typeOfValue = 0;

            areaOfComments = false; 
            for_loop = false;
            repeatCode = false; 
            varArgumentsCall = false; 
            if_ReturnFalse = false;
            valueIsVar = false;
            stringIsTrue = false;
            valueAdding = false;
            variableNameAdding = false;
            functionAdding = true; 
            argumetsAdding = false; 
            stringStarted = false;
            missSymbol = false;      
    }

    void _AnalysCode( char chars[], int count_elements ){

        
        for(i = 0; i < count_elements; i++)
        {
            char symbol_later = chars[i-1]; // Символ перед now
            char symbol_now = chars[i]; // Символ идущий дальше по вектору
            char symbol_next = chars[i+1]; // Символ следующий дальше

        //     // Счетчики неких штук
        //     if (stringIsTrue == false && symbol_now == ';'){
        //         dbstats.countCalls += 1;
        //     }

        //     dbstats.countSmbls += 1;

        // //-=-=-=-=-
            // std::cout << func << " | " << lastCall << std::endl; 

            // Перехватка комментариев
            if (areaOfComments && symbol_now != START_OF_COMMENTS){
                continue;
            }

            if (symbol_now == START_CODE and codeStarted == false){
                codeStarted = true; // Начало анализа
                continue;
            }
            // WORKONIT нужно ли это нам?
            if(symbol_now == START_CODE and codeStarted){
                if (DebugMetaSwitch){
                    std::cout << "size of chars: " << sizeof &chars << std::endl;      
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

            if (void_do){
                if (symbol_now == '}'){
                    i = void_backIndx;
                }
            }
            
            if (skipFuncBlock){
                if(symbol_now == '}'){
                    skipFuncBlock = false;
                }
                continue;
            }
            
            // Если выполняется цикл и находим конец его блока
            if (for_loop && symbol_now == '}' && if_ReturnFalse == false ){
                // Проверяем условие цикла
                if (if_ComparisonSupport(for_comparison)){
                    // Если условие верно, то воспроизводим кусок кода еще раз
                    i = loop_backIndx;
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
                    _getType(symbol_next); // Определяем тип
                    missSymbol = true; // Для пропуска символа после тильды
                    continue;
                }

                if ((symbol_now == TAKE_SPACE || symbol_now == '.') && (!stringIsTrue && !valueAdding)){
                    functionAdding = false;
                    variableNameAdding = true;
                    continue;
                }
            
            // Всякого рода операции, допустим var++;
        // -       =========   ==========

                // Обработка var++;

                if (functionAdding && symbol_now == END_OF_LINE && symbol_later == '+'){
                    _incrementP(func); //  P - plus  
                    func = EMPTY;
                    continue;
                }

                // Обработка var--; 
                if (functionAdding && symbol_now == END_OF_LINE && symbol_later == '-'){
                    _incrementM(func); // M - minus
                    func = EMPTY;
                    continue;
                }

                // Обработка комментариев

                if (areaOfComments && symbol_now == START_OF_COMMENTS ){
                    areaOfComments = false;
                    continue;
                }
                

                if (functionAdding && symbol_now == START_OF_COMMENTS && !areaOfComments){
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
                        

                        _addToList (typeOfValue, value);
    
                        value = EMPTY;
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
                
                    if (stringIsTrue == false and symbol_now == END_OF_LINE){ // если ; не относиться к строке, то
                        // Пора уже добавить переменную
                        _putValueToVar(); 
                        
                        // Сброс переменных
                        _rebornSettings();
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

                            // factorial()
                            if (lastCall == FACTORIAL){
                                // Самба белого мотылька, у открытого огонька --- east. "Аккуратней с памятью"
                                int *local = new int; 
                                *local = factorial(listOfManyArguments);// Возвращение факториала
                                putValueToVar(variableName, std::to_string(*local));
                                delete local;
                            }
                            // from();
                            if (lastCall == LIST_FROM){
                                // Скармливаем все данные из строки
                                functionFROM(variableName, listOfManyArguments);
                            }
                            
                            // angela();
                            if (lastCall == ANGEL_FUNCTION){
                                // Запрос на возвращение элемента
                                
                                if (listOfManyArguments.size() > 2){
                                    _namesOfAllVariables[variableName] = STRING;
                                    _vrS[variableName] = Angel(listOfManyArguments)[0];
                                }else{// Если возвращает просто вектор
                                    _namesOfAllVariables[variableName] = LIST_STRING; // Так как angela(); возвращает вектор строк
                                    _vrL[variableName] = Angel(listOfManyArguments);
                                }
                            }
                            
                            listOfManyArguments.clear();
                            continue;
                        }

                    }

                    if (symbol_now == '(' && !stringIsTrue){
                        varArgumentsCall = true; 
                        lastCall = value;
                        value = EMPTY;
                        continue;
                    } 

                // Добавление значения

                    if (symbol_now != END_OF_LINE && symbol_now != ' ' && varArgumentsCall == false){
                        value += symbol_now;
                    }

                    
                }

                
                // Имя переменной
                if (variableNameAdding == true)
                {
                    // WORKONIT предпосылки  к пиздецу в структкре кода -- работает - не трогай
                    // Я без понятия что это
                    if (chars[i-1] != ')' && symbol_now == END_OF_LINE){
                        variableNameAdding = false;
                        functionAdding = true;
                        _namesOfAllVariables.emplace(variableName, typeForVariable);
                        variableName = EMPTY;
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
                    repeat_backIndx = i+1;
                    func = EMPTY;
                }

                if (symbol_now == POINT_SYN_CHAR && functionAdding && repeatCode == false){
                    repeat_backIndx = i+1;
                    repeatCode = true;
                    continue; // Пропускаем ':'
                }
                // Объясняю. У нас всегда собирается func, а значит     
                // мы можем воспользоваться этим, ну то есть кол-во раз выполнения уже лежит в func
                // в общем, DB тебе в помощь, я объяснил как мог.
                if (repeatCode && symbol_now == POINT_SYN_CHAR){
                    if (timesForRepeat == -1){
                        if (_namesOfAllVariables[func] == NON_TYPE){
                            timesForRepeat = std::stoi(func);
                        }else{
                            if (_namesOfAllVariables[func] != _INT){
                                // WORKONIT исключение
                                std::cout << "WORKONIT" << std::endl;
                            }else{
                                timesForRepeat = _vrI[func];
                            }
                        }
                    }
                    timesForRepeat -= 1;
                    // Если задача не выполнена
                    if (timesForRepeat != 0){
                        i = repeat_backIndx;// Возвращаем цикл на метку, ну изменяем итерацию                       
                    }else{
                        _rebornSettings();
                    }

                    functionAdding = true;
                    func = EMPTY;
                    continue;
                }
                
    // =====================================================================================================================

                // ## Функции и методы, аргументы, условия
                

                    //                  Упоминание для условий
                if (symbol_now == END_OF_LINE || symbol_now == '{' && argumetsAdding == false && functionAdding == false){

                // Ветвление    
                    if (lastCall == IF_SYN || lastCall == EMPTY){ // ----- last == EMPTY Для облегчения синтаксиса 
                        // Скормлеваем функции те аргументы, что удалось найти, если вернуло false, то скипаем все, что в условии
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
                        // add();
                        if (lastCall == ADD){
                            add(listOfManyArguments);
                        }
                        // remove();
                        if (lastCall == REMOVE){
                            remove(listOfManyArguments);
                        }
                    }

                // For

                    if  (lastCall == FOR_SYN || lastCall == EXTRA_SYN_FOR){// ----- last == EXTRA_SYN_FOR Для облегчения синтаксиса -----  east
                        for_comparison = listOfManyArguments; // Перекидываем аргументы, в специальный список для for()
                        for_loop = true;
                        loop_backIndx = i+1;   
                    } 


                //============
                // Пользовательские функции
                    // Если функция существует
                    if (ins_Voids[lastCall] != 0){
                        void_backIndx = i;
                        void_do = true;
                        i = ins_Voids[lastCall];
                    }

                // Методы с поддержкой только одного аргумента
                    // void (){}
                    if (lastCall == FUNC_WARN){
                        WorkVoid(argumets, i+1);
                        skipFuncBlock = true;
                    }
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
                    if (lastCall == BUBBLE_SORT){
                        bbl_sort(argumets);
                    }       
                    if (lastCall == CRASH_SCRIPT){
                        CrashScript();
                    }   
                    
                //===================
                    listOfManyArguments.clear();
                    functionAdding = true;
                    argumets = EMPTY;
                    lastCall = EMPTY;
                    continue;
                }

                if (argumetsAdding){
                    // Символы для определения сравнения - это именно второй символ после '=':  =>,  =<,  ==. 
                    const std::vector<char> charsForIfComparison = {'=','>','<','!'};
                    // Если использованнно ветвление if(num == 10){} и for(a < 10){}
                    if (lastCall == IF_SYN || lastCall == EMPTY || lastCall == FOR_SYN || lastCall == EXTRA_SYN_FOR)
                    { // ----- last == EMPTY Для облегчения синтаксиса -----  east.
                        if (CheckElem(symbol_now, charsForIfComparison) && !stringIsTrue ){
                            listOfManyArguments.push_back(argumets); // Добавляем num из примера выше
                            argumets = EMPTY;
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
                        continue;
                    }

                    if (!stringIsTrue && symbol_now == '"'){
                        stringIsTrue = true;
                    }
                    // Если введенны несколько аргументов sout("Hello", 300);
                    if (symbol_now == ',' && !stringIsTrue){
                        // Добавляем один из введенных аргументов
                        listOfManyArguments.push_back(argumets);
                        argumets = EMPTY; // Нашли аргумент, добавили, переходим к следующему
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
                    func = EMPTY;
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
    }

public:
    /*
    Конструктору нужно прочесть файл для того, чтобы начать классу работу с ним.
    */
    AniolScriptParserCode(std::string FileName)
    {
        
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

        for(int i = 0; i < filesStrings -> size(); i++){

            const int len = (*filesStrings)[i].length();
            char charArrayOfCode[len+1];
    
            // Копируем содержимое строки и переводим в массив
            std::strcpy(charArrayOfCode, (*filesStrings)[i].c_str());
            for (int i = 0; i < len; i++)
                timeArrayOfChar -> push_back(charArrayOfCode[i]);
        
        }
        int j = 0, number_chars = timeArrayOfChar  -> size();
        char arrayOfChar [number_chars];
        
        for(char x : *timeArrayOfChar){ 
            arrayOfChar[++j] = x; 
        }

    // Очитка памяти. Мы не знаем сколько строк будет в файле .ks и оставлять их я не вижу смысла.
        charArrayOfCode -> clear();
        delete charArrayOfCode;

        filesStrings -> clear();
        delete filesStrings;

        timeArrayOfChar -> clear();
        delete timeArrayOfChar;
    // =================================================

        _AnalysCode(arrayOfChar, number_chars );
        // Если строки закончились, переходим к анализу
    }  
    ~AniolScriptParserCode()
    {
        std::cout << "raed file" << std::endl;
    }
};

std::__cxx11::string Menu(){
    int i = 0;
    std::__cxx11::string fileName, command_line;

    for(;i < 2; i++){ std::cout << "| " << std::endl; }

    std::cout << "| /ls of $dir: "; system("ls");

    std::cout << "| -> Choose file or write his name: ";
    std::getline(std::cin, fileName);
    // Составляем команду, выводим содерживое файла
    command_line = "more " + fileName; system(command_line.c_str());
    
    return fileName;
}


int main() {
    // std::cout << Menu();

    // -- HARDCODED
    AniolScriptParserCode Code("Meta.ks");

    // std::cout << AutoTypeForValue("10.1");
    system("pause>nul");
}

