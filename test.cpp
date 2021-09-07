#include <iostream>
#include <conio.h>
#include <windows.h>

int xOfMouse,
    yOfMouse;

int rgbColor[3];

using namespace std;

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
        // SetCursorPos(xOfMouse, yOfMouse);
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
            
            cout << "Position saved";
            break;
        }
        Sleep( 25 );
    }
    
}

int main()
{
    GetPosition();
    SetPixels();
    CheckColors();
}