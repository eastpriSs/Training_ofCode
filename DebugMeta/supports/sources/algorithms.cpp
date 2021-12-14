#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cctype>
#include <windows.h>


std::map< char, std::string > morse =
{
{'A',".-"},
{'B',"-..."},
{'C',"-.-."},
{'D',"-.."},
{'E',"."},
{'F',"..-."},
{'G',"--."},
{'H',"...."},
{'I',".."},
{'J',".---"},
{'K',"-.-"},
{'L',".-.."},
{'M',"--"},
{'N',"-."},
{'O',"---"},
{'P',".--."},
{'Q',"--.-"},
{'R',".-."},
{'S',"..."},
{'T',"-"},
{'U',"..-"},
{'V',"...-"},
{'W',".--"},
{'X',"-..-"},
{'Y',"-.--"},
{'Z',"--.."},
{'0',"-----"},
{'1',".----"},
{'2',"..---"},
{'3',"...--"},
{'4',"....-"},
{'5',"....."},
{'6',"-...."},
{'7',"--..."},
{'8',"---.."},
{'9',"----."},
{'.',".-.-.-"},
{',',"--..--"},
{'?',"..--.."},
{'=',"-...-"},
{' ', "/"},
};

void TextToClipboard(std::string transletedText)
 {
    if (OpenClipboard(0))
    {
        HGLOBAL hMem  = GlobalAlloc(GMEM_MOVEABLE, transletedText.size()+1);
        memcpy(GlobalLock(hMem), transletedText.data(), transletedText.size()+1);
 
        OpenClipboard (0);
        EmptyClipboard( );
        SetClipboardData(CF_TEXT, hMem);
        CloseClipboard( );
        GlobalUnlock(hMem);
        CloseClipboard();

    }
}

void morseTranslator(std::string str){
    std::vector<char> lettersOfStr(str.begin(), str.end());
    std::string transleted = "";

    for(int i = 0; i < lettersOfStr.size(); i++){
        char letterNow = std::toupper(lettersOfStr[i]);
        transleted += "   ";
        transleted += morse[letterNow];

    }
    TextToClipboard(transleted);

}


int main(){
    
    std::string text;
    
    while (text != " ")
    {
        std::cout << "translate it: ";
        std::getline(std::cin, text);
        morseTranslator(text);
    }

}