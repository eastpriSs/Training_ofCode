#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cstring>


const char OPENED_BRACKET = '(';
const char CLOSED_BRACKET = ')';

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

double MathExpressionParserD(std::string MathExpression){
    return 0.0;
}

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
    std::cout << "Db" << num1 << " | " << num2 << std::endl;
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
    // writevec(steckOfNumerals); // <DB>
    int lastResult = ActionWorker(returnTop(steckOfActions), steckOfNumerals[steckOfNumerals.size()-2], returnTop(steckOfNumerals));
    steckOfNumerals.erase(steckOfNumerals.end()-2, steckOfNumerals.end());
    steckOfActions.pop_back();
    steckOfNumerals.push_back(lastResult);
    // writevec(steckOfNumerals); // < DB>
    if(typeOfGoal == 1){
        if(steckOfActions[steckOfActions.size()-2] == '('){
            CountSteck(0);
        }
    }
}

std::map<std::string, int> test = {{"num", 10 }};
std::map<std::string, int> VarList = {{"num", 1 }};

double MathExpressionParserI(std::string MathExpression){

    std::string Number = "";
    bool NumberTakes = true;
    bool nameVarAdd = false;

    const std::vector<char> extraSymbls = {CLOSED_BRACKET, OPENED_BRACKET};
    const std::vector<char> ValidActions = {'+','-','*','/'};
    const std::vector<char> nums = {'0','1','2','3','4','5','6','7','8','9','.'};
    // Сделано для того, чтобы если будет участвовать переменная код не загнулся.
    
    std::vector<char> MathExpressionChars(MathExpression.begin(), MathExpression.end());

    for(char parsChar : MathExpressionChars){

        if (NumberTakes && CheckElem(parsChar, nums)){
            Number += parsChar;
            continue;
        }


        if (CheckElem(parsChar, ValidActions) || CheckElem(parsChar, extraSymbls)){
            
            if (Number != ""){
                steckOfNumerals.push_back(std::stod(Number));  
                writevec(steckOfNumerals);       
            }
            steckOfActions.push_back(parsChar);

            if (parsChar == CLOSED_BRACKET){
                steckOfNumerals.push_back(std::stod(Number));
                CountSteck(1);
            }

            // Апендикс
            if(steckOfActions.size() == 0){
                steckOfActions.push_back(parsChar);
            }else{
                // Если открыты скобки
                if(returnTop(steckOfActions) == OPENED_BRACKET){
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
            writevec(steckOfNumerals);
            NumberTakes = true;
            Number = "";
        }
    }
    
    

    // // Если в стеке еще есть задача, просчитываем и выводим
    // if(steckOfNumerals.size() == 2){
    //     std::cout << ActionWorker(steckOfActions[0], returnTop(steckOfNumerals), steckOfNumerals[0]);
    // }else{
    //     // Если в стеке одно число, возникает при допустим 2+2 
    //     std::cout << steckOfNumerals[0] << std::endl;
    // }
    
}


int main(){
    // WORKONIT
    MathExpressionParserI("(2.1+2.2/2.3+2.4)*2.4-2.5");
}