#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstring>


// Стек для чисел
std::vector<double> steckOfNumerals = {}; // Че делать с типом данных?
// Стек для действий
std::vector<char> steckOfActions = {};

std::map<char, int> priorityOfActions = 
{
    {'+',1},
    {'-',1},
    {'*',2},
    {'/',2}
};


// only for chars and only for this goal
bool CheckElem(char NeedToFind, const std::vector<char> List){
    for(int num = 0; num < List.size(); num++){
        if(List[num] == NeedToFind){
            return true;
        }
    }
    return false;
}
// <DB>
void writevec(std::vector<auto> vec){
    for(int elem = 0; elem < vec.size(); elem++){
        std::cout << elem << " . " <<  vec[elem] << " | ";  
    }
    std::cout << std::endl;
}
// Топ стека
auto returnTop(std::vector<auto> vec){
    return vec[vec.size()-1];
}
// Не знаю зачем, может понадобиться, аналог pop на пайтоне
auto pop(std::vector<auto> vec){
    auto lastelem = vec[vec.size()-1];
    vec.pop_back();
    return lastelem; 
}

// Просто просчитывает легкие задачки
double ActionWorker(char action, double num1, double num2)
{
    if(action == '+'){
        return num1 + num2;
    }else if(action == '-'){
        return num1 - num2;
    }else if(action == '*'){
        return num1 * num2;
    }else if(action == '/'){
        return num1 / num2;
    }
}

/* typeOfGoal отвечает за алгоритм просчета стека, если у нас поступает код 1, то это значит мы считаем выражения в скобках */

void CountSteck(int typeOfGoal){
    // writevec(steckOfNumerals);// <DB>
    int lastResult = ActionWorker(returnTop(steckOfActions), steckOfNumerals[steckOfNumerals.size()-2], returnTop(steckOfNumerals));
    steckOfNumerals.erase(steckOfNumerals.end()-2, steckOfNumerals.end());
    steckOfActions.pop_back();
    steckOfNumerals.push_back(lastResult);
    // writevec(steckOfNumerals); < DB>
    if(typeOfGoal == 1){
        if(steckOfActions[steckOfActions.size()-2] == '('){
            CountSteck(0);
        }
    }
}

std::map<std::string, double> test = {{"num", 10 }};

double MathExpressionParserI(std::string MathExpression){

    std::string nameVar = "";
    std::string bigNumber = "";
    bool NumberTakes = false;
    bool nameVarAdd = false;

    const std::vector<char> ValidActions = {'+','-','*','/','(',')'};
    // Сделано для того, чтобы если будет участвовать переменная код не загнулся.
    const std::vector<char> Nums = {'0','1','2','3','4','5','6','7','8','9'};
    
    std::vector<char> MathExpressionChars(MathExpression.begin(), MathExpression.end());

    for(int i = 0; i < MathExpressionChars.size(); i++){

        char parsChar = MathExpressionChars[i];
        // Вынес за основное условие, чтобы быстрее работало
        if(NumberTakes){
            bigNumber += parsChar; // Собираем число
        }

        if(nameVarAdd && CheckElem(parsChar, ValidActions)){
            nameVarAdd = false;
            steckOfNumerals.push_back(test[nameVar]);
            nameVar = "";
        }

        if(CheckElem( parsChar, ValidActions) == false && CheckElem(parsChar, Nums) == false){
            nameVar += parsChar;
            nameVarAdd = true;
            // continue;
        }


        if(MathExpressionChars.size() == i+1){// Если конец примера
            if(nameVar != ""){
                steckOfNumerals.push_back(test[nameVar]);
                nameVar = "";
            }
            else if(bigNumber == ""){// Если нету больших чисел
                int N = parsChar - '0';
                steckOfNumerals.push_back(N);
            }else{
                steckOfNumerals.push_back(std::stod(bigNumber));
            }
            CountSteck(0);// Мохинации
            continue;  
        }


        if(parsChar == ')'){
            if(nameVarAdd){
                steckOfNumerals.push_back(test[nameVar]);
                nameVar = "";
                nameVarAdd = false;
            }   
            // writevec(steckOfActions);
            CountSteck(1);
            continue;
        }

        if(CheckElem(parsChar, Nums)){

            // Если мы нашли нумерал, но за ним еще один.
            if(CheckElem(MathExpressionChars[i+1], Nums) && NumberTakes == false){
                NumberTakes = true; 
                bigNumber += parsChar;
                continue;
                // Если мы следующий элемент не нумерал.
            }
            else if(CheckElem(MathExpressionChars[i+1], Nums) == false && NumberTakes == true)
            {
                NumberTakes = false;
                steckOfNumerals.push_back(std::stod(bigNumber));// Преобразуем наше число в инт
                bigNumber = "";
                continue;
            }            

            int N = parsChar - '0';// Ковертируем чар в нумерал через ASCII

            steckOfNumerals.push_back(N);
            continue;
        }
        if(CheckElem(parsChar, ValidActions) == true){
            
            // Апендикс
            if(steckOfActions.size() == 0){
                steckOfActions.push_back(parsChar);
            }else{
                // Если открыты скобки
                if(returnTop(steckOfActions) == '('){
                    steckOfActions.push_back(parsChar);
                    continue;
                } 
                // Сравниваем приоритеты знаков
                if(priorityOfActions[parsChar] > priorityOfActions[returnTop(steckOfActions)]){
                    steckOfActions.push_back(parsChar);
                }else{
                    CountSteck(0);
                    steckOfActions.push_back(parsChar);
                }
            }
        }
    }

    // Если в стеке еще есть задача, просчитываем и выводим
    if(steckOfNumerals.size() == 2){
        return ActionWorker(steckOfActions[0], returnTop(steckOfNumerals), steckOfNumerals[0]);
    }else{
        // Если в стеке одно число, возникает при допустим 2+2 
        return steckOfNumerals[0];
    }
    
}

int main(){
    // WORKONIT
    std::cout << MathExpressionParserI("(2+num/2+2)*2-num") << std::endl;
}