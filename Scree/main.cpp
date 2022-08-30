#include <Windows.h>
#include <thread>
#include <iostream>
#include <fstream>
#include <Windows.h>

#pragma comment(lib, "Winmm.lib")

INT save_screenshot(HDC& hdc, HBITMAP& hBit, const short& h, const short& w)
{

    if( hdc==NULL ) {
        printf("Couldn't create device context\n");
        return 1;
    }
                            
    DWORD dwWidth, dwHeight, dwBPP, dwNumColors;

    dwWidth  = w;
    dwHeight = h;
    
    dwBPP    = GetDeviceCaps(hdc, BITSPIXEL);
    if( dwBPP <= 8 ) {
        dwNumColors = GetDeviceCaps(hdc, NUMCOLORS);
        dwNumColors = 256;
    } else {
        dwNumColors = 0;
    }
 
    // Create compatible DC.
    HDC hdc2 = CreateCompatibleDC(hdc);
    if( hdc2==NULL ) {
        DeleteDC(hdc);
        printf("Couldn't create compatible device context\n");
        return 1;
    }

    LPVOID pBits;
    HBITMAP bitmap;
    BITMAPINFO bmInfo;
 
    bmInfo.bmiHeader.biSize         = sizeof(BITMAPINFOHEADER);
    bmInfo.bmiHeader.biWidth            = dwWidth;
    bmInfo.bmiHeader.biHeight           = dwHeight;
    bmInfo.bmiHeader.biPlanes           = 1;
    bmInfo.bmiHeader.biBitCount     = (WORD) dwBPP;
    bmInfo.bmiHeader.biCompression      = BI_RGB;
    bmInfo.bmiHeader.biSizeImage        = 0;
    bmInfo.bmiHeader.biXPelsPerMeter    = 0;
    bmInfo.bmiHeader.biYPelsPerMeter    = 0;
    bmInfo.bmiHeader.biClrUsed          = dwNumColors;
    bmInfo.bmiHeader.biClrImportant = dwNumColors;
    
    bitmap=CreateDIBSection(hdc, &bmInfo, DIB_PAL_COLORS, &pBits, NULL, 0);
    if( bitmap==NULL ) {
        DeleteDC(hdc);
        DeleteDC(hdc2);
        printf("Couldn't create compatible bitmap\n");
        return 1;
    }
 
    HGDIOBJ gdiobj = SelectObject(hdc2, (HGDIOBJ)bitmap);
    if( (gdiobj==NULL) || (gdiobj==(void*)(LONG_PTR)GDI_ERROR) ) {
        DeleteDC(hdc);
        DeleteDC(hdc2);
        printf("Couldn't select bitmap\n");
        return 1;
    }
    if( !BitBlt(hdc2, 0,0, dwWidth, dwHeight, hdc, 0,0, SRCCOPY) ) {
        DeleteDC(hdc);
        DeleteDC(hdc2);
        printf("Could not copy bitmap\n");
        return 1;
    }
    
    RGBQUAD colors[256];
    if( dwNumColors!=0 )
        dwNumColors = GetDIBColorTable(hdc2, 0, dwNumColors, colors);

    BITMAPFILEHEADER bmfh;
    BITMAPINFOHEADER bitmapinfoheader;
 
    bmfh.bfType             = 0x04D42;
    bmfh.bfSize             = ((dwWidth * dwHeight * dwBPP)/8) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (dwNumColors * sizeof(RGBQUAD));
    bmfh.bfReserved1        = 0;
    bmfh.bfReserved2        = 0;
    bmfh.bfOffBits          = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (dwNumColors * sizeof(RGBQUAD));
    bitmapinfoheader.biSize             = sizeof(BITMAPINFOHEADER);
    bitmapinfoheader.biWidth            = dwWidth;
    bitmapinfoheader.biHeight           = dwHeight;
    bitmapinfoheader.biPlanes           = 1;
    bitmapinfoheader.biBitCount         = (WORD)dwBPP;
    bitmapinfoheader.biCompression      = BI_RGB;
    bitmapinfoheader.biSizeImage        = 0;
    bitmapinfoheader.biXPelsPerMeter    = 0;
    bitmapinfoheader.biYPelsPerMeter    = 0;
    bitmapinfoheader.biClrUsed          = dwNumColors;
    bitmapinfoheader.biClrImportant     = 0;
    
    std::ofstream file;
    file.open("image.bmp", std::ios::binary| std::ios::trunc | std::ios::out);
    file.write((char*)&bmfh, sizeof(BITMAPFILEHEADER));
    file.write((char*)&bitmapinfoheader, sizeof(BITMAPINFOHEADER));
 
    if( dwNumColors!=0 )
        file.write((char*)colors, sizeof(RGBQUAD)*dwNumColors); 
    file.write((char*)pBits, (dwWidth*dwHeight*dwBPP)/8);

    DeleteObject(bitmap);
    DeleteDC(hdc2);
    DeleteDC(hdc);
    
    return 0;
}

void make_screenshot()
{
    HWND hwnd;
    int x1,y1,
        x2,y2,
        w,h; 

    x1 = GetSystemMetrics(SM_XVIRTUALSCREEN);
    y1 = GetSystemMetrics(SM_YVIRTUALSCREEN);
    x2 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    y2 = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    
    w = GetSystemMetrics(SM_CXSCREEN);
    h = GetSystemMetrics(SM_CYSCREEN);

    HDC hScreen = GetDC(NULL);
    HDC hDC = CreateCompatibleDC(hScreen);
    HBITMAP hbitmap = CreateCompatibleBitmap(hScreen, w, h);
    HGDIOBJ oldObj = SelectObject(hDC, hbitmap);
    BOOL bret = BitBlt(hDC, 0, 0, w, h, hScreen, x1, y1, SRCCOPY);

    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, hbitmap);
    CloseClipboard();
    
    save_screenshot(hScreen, hbitmap, h, w);
}

INT main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    // Отслеживание клавиш
    while (true) {

        // CNTRL+HOME скриншот
        if (GetAsyncKeyState(VK_CONTROL)) 
        {
            if (GetAsyncKeyState(VK_HOME)) 
            {
                std::thread th(make_screenshot);
                th.join();
                mciSendString("play this_play_when_screen.mp3", NULL, 0, NULL);
                Sleep(100);
            }
        }
        // HARDCODED
        // CNTRL+RSHIFT выход из программы
        if (GetAsyncKeyState(VK_CONTROL)) 
        {
            if (GetAsyncKeyState(VK_RSHIFT)) 
            {
                break;
            }
        }
        Sleep(500);
    }
    return 0;
}
