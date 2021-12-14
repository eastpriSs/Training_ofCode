#include <iostream>
#include <fstream>



 /*

[ - >> ]      This log of {date}
\n
[ $ ] code in function - {function_name}, goes to with this arguments - {sended_argumets}.
[ $ ] 

*/





void makeLog(std::vector CodeOptions) // Должен принемать контейнер с информацией о коде.
{
    std::ofstream out;          // поток для записи
    out.open("logs/suicide.txt"); // окрываем файл для записи
    if (out.is_open())
    {
        out << 1 << std::endl;
    }
     
    std::cout << "End of program" << std::endl;
}