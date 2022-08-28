#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <string>

#define FILE "settings.cfg"
#define CMD "start dist\\send_msg" 

int xOfMouse,
    yOfMouse;

int rgbColor[3];

using namespace std;

void send_msg(){
    system(CMD);
}


bool readSettings(){
    int i = 0;

    std::string line;
    int pos[2];

    std::ifstream in(FILE); // окрываем файл для чтения
    if (in.is_open())
    {
        while (getline(in, line, ','))
        {
            pos[i] = std::stoi(line);
            i++;
        }
    }else{
        return false;
    }
    in.close();// закрываем файл

    xOfMouse = pos[0];
    yOfMouse = pos[1];
}

void writeSettings(int x, int y){
    std::ofstream out(FILE, std::ios::ate);
    if (out.is_open())
    {
        out << x << "," << y;
    }
    out.close();    
}

void SetPixels(){
    HDC      dc = GetDC(NULL);
    COLORREF color = GetPixel(dc, xOfMouse, yOfMouse);
    rgbColor[0] = GetRValue(color);
    rgbColor[1] = GetGValue(color);
    rgbColor[2] = GetBValue(color);
    ReleaseDC(NULL, dc);
}

void CheckColors(){
    int lastColor = rgbColor[0];
    SetPixels();
    int newColor = rgbColor[0];

    if (lastColor == newColor){
        CheckColors();
    }else{
        Sleep(100);
        SetCursorPos(xOfMouse, yOfMouse);
        mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, xOfMouse, xOfMouse, 0, 0);
    }
    
}

void GetPosition(){
    POINT p;

    while (true)
    {
        int buttom = getch();

        if (buttom == VK_RETURN){
            GetCursorPos(&p);
            xOfMouse = p.x;
            yOfMouse = p.y;
            
            cout << "Position saved" << std::endl;
            writeSettings(xOfMouse, yOfMouse);
            break;
        }
        Sleep( 25 );
    }
    SetPixels();
}

int main()
{
    readSettings()?SetPixels():GetPosition();
    std::cout << "Checking start" << std::endl;
    CheckColors();
    send_msg();
}
