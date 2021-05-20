#include <iostream>
#include <cstdlib>
#include <vector>




    std::vector<int> all_numbers = {};
    std::vector<int> numbers_even = {};
    std::vector<int> numbers_odd = {};


int main(){


    std::cout << "Sort array with 100 random numbers to even and to odd." << std::endl;

    std::cin.ignore();

    for(int i = 0; i < 100; i++ ){

        int number = rand();

        if(number % 2 == 0){
            std::cout << "Value is even: " << number  << std::endl;
            numbers_even.push_back(number);
        }else{
            std::cout << "Value is odd: " << number  << std::endl;            
            numbers_odd.push_back(number);
        }

        all_numbers.push_back(number);


    }   
    
    std::cout << std::endl;
    std::cout << "======================" << std::endl;
    std::cout << "All numbers:" << std::endl;
    for(int i = 0; i < all_numbers.size(); i++){
        std::cout << all_numbers[i] << " ; ";
    }
    std::cout << std::endl;
    std::cout << "======================" << std::endl;
    std::cout << "Even numbers:" << std::endl;
    for(int i = 0; i < numbers_even.size(); i++){
        std::cout << numbers_even[i] << " ; ";
    }
    std::cout << std::endl;
    std::cout << "======================" << std::endl;
    std::cout << "Odd numbers:" << std::endl;
    for(int i = 0; i < numbers_odd.size(); i++){
        std::cout << numbers_odd[i] << " ; ";
    }

    std::cin.ignore();
}