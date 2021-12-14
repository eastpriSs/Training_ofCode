#include <iostream>   
#include <string>
#include <cmath>

// Получаем число и сс
void InputNum(int& Nm, int& NttF, int& NttT){
    std::cin >> Nm >> NttF >> NttT;
}

void OutMathEx (int numeral, int notation_T, int div){
    std::cout << numeral << " / " << notation_T << " = "<< div << std::endl;
}

void OutMathEx (auto& Num_el, auto& ntF, auto& deg, int& res){
    std::cout << Num_el << " * " << ntF << " ** " << deg << " = "<< res << std::endl;
}

void Translate (int numeral, int notation_F, int notation_T  ){
    std::string numeral_els = std::to_string(numeral);
    short degree = numeral_els.size() - 1;
    int N_el, translated_el, translated_num = 0;

    if (notation_F == 10 and notation_T == 2){
        while (numeral != 1)
        {
            OutMathEx(numeral, notation_T, numeral%notation_T);
            numeral /= 2;        
        }
        OutMathEx(numeral, notation_T, numeral%notation_T);
    }
    std::cout << "\t\t^" << std::endl;
    std::cout << "\t\t|" << std::endl;
    std::cout << "\t\t|" << std::endl;
}

int Translate (int numeral, int notation_F  ){
    std::string numeral_els = std::to_string(numeral);
    short degree = numeral_els.size() - 1;
    int N_el, translated_el, translated_num = 0;

    auto tranlate_el = [](auto Num_el, auto ntF, auto deg ) { 
        return Num_el * pow(ntF, deg);
    };

    for(char N : numeral_els){
        N_el = (int)N - 48;
        translated_el = tranlate_el(N_el, notation_F, degree);      
        translated_num += translated_el;

        OutMathEx(N_el, notation_F, degree, translated_num);
        degree--;
    }

    return translated_num;
}

int main(){
    int num, notation_F, notation_T ;
    InputNum(num, notation_F, notation_T);
    Translate(num, notation_F, notation_T);
}