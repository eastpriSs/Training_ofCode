#include <Windows.h>
#include <thread>
#include <iostream>
#include <fstream>
#include <Windows.h>

// cd "d:\WORKONIT\cpp_experience\Scree\" ; if ($?) { g++ main.cpp -lgdi32 -lwinmm  -fconcepts -o main } ; if ($?) { .\main }
#pragma comment(lib, "Winmm.lib")

class Parser
{
public:

    Parser();
    void parse(std::string&&);

    std::string resolution_w;
    std::string resolution_h;

    std::string first_button;
    std::string second_button; 

    std::string folder_link;

private:    

};

Parser::Parser()
: resolution_h(),
  resolution_w(),
  first_button(),
  second_button(),
  folder_link()
{
}

void Parser::parse(std::string&& link)
{
    int line_number = 0;
    std::string line;
    std::ifstream myfile (link);

    if (myfile.is_open())
    {
        while ( line_number <= 4 )
        {
            getline (myfile,line);
            
            line_number++;
            switch ( line_number ) { 
            // Разрешение
            case 1: 
            {
                unsigned short i = 0; 
                while ( isdigit(line[i]) )
                {
                    resolution_w += line[i];    
                    i++;
                }
                i++; // Пропускаем сепаратор
                while ( isdigit(line[i]) )
                {
                    resolution_h += line[i];    
                    i++;
                }
                break;
            }
            // Первая кнопка
            case 2: 
            {
                unsigned short i = 0; 
                while ( line[i] != ';' )
                {
                    first_button += line[i];    
                    i++;
                }
                break;
            }
            // Вторая кнопка
            case 3: 
            {
                unsigned short i = 0; 
                while ( line[i] != ';' )
                {
                    second_button += line[i];    
                    i++;
                }
                break;
            }
            // Папка
            case 4: 
            {
                unsigned short i = 0; 
                while ( line[i] != ';' )
                {
                    folder_link += line[i];    
                    i++;
                }
                break;
            }

            }
        }
        myfile.close();
    }
    else std::cout << "Unable to open file"; 

    std::cout << resolution_w << '\n';
    std::cout << resolution_h << '\n';
    std::cout << first_button << '\n';
    std::cout << second_button << '\n';
    std::cout << folder_link << '\n';

}

const std::string get_name_file()
{
    return "image.bmp";
}

INT save_screenshot(HDC& hdc, HBITMAP& hBit, const short& h, 
                    const short& w, Parser&& dt)
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
    file.open( dt.folder_link + get_name_file(), std::ios::binary| std::ios::trunc | std::ios::out);
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

void make_screenshot(Parser&& dt)
{
    HWND hwnd;
    int x1,y1,
        x2,y2,
        w,h; 

    x1 = GetSystemMetrics(SM_XVIRTUALSCREEN);
    y1 = GetSystemMetrics(SM_YVIRTUALSCREEN);
    x2 = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    y2 = GetSystemMetrics(SM_CYVIRTUALSCREEN);

    if ( dt.resolution_h == "0" || dt.resolution_w == "0" ) {    
        w = GetSystemMetrics(SM_CXSCREEN);
        h = GetSystemMetrics(SM_CYSCREEN);
    } else {
        w = std::stoi(dt.resolution_w);
        h = std::stoi(dt.resolution_h);
    }

    HDC hScreen = GetDC(NULL);
    HDC hDC = CreateCompatibleDC(hScreen);
    HBITMAP hbitmap = CreateCompatibleBitmap(hScreen, w, h);
    HGDIOBJ oldObj = SelectObject(hDC, hbitmap);
    BOOL bret = BitBlt(hDC, 0, 0, w, h, hScreen, x1, y1, SRCCOPY);

    OpenClipboard(NULL);
    EmptyClipboard();
    SetClipboardData(CF_BITMAP, hbitmap);
    CloseClipboard();
    
    save_screenshot(hScreen, hbitmap, h, w, std::move(dt));
}

void detect_pressed()
{
    
}

INT main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    Parser data;
    data.parse("cfg/settings.txt");

    auto first_button  = VK_CONTROL;
    auto second_button = VK_HOME;

    if ( data.first_button != "0" )
    {
        if ( std::tolower(data.first_button) == "shift"   )      first_button = VK_SHIFT   ;
        else if ( std::tolower(data.first_button) == "control" ) first_button = VK_CONTROL ;
        else if ( std::tolower(data.first_button) == "rshift"  ) first_button = VK_RSHIFT  ;
        else if ( std::tolower(data.first_button) == "rcontrol") first_button = VK_RCONTROL;
    }

    if ( data.second_button != "0" )
    {
        if ( std::tolower(data.second_button) == "shift"   )      second_button = VK_SHIFT   ;
        else if ( std::tolower(data.second_button) == "control" ) second_button = VK_CONTROL ;
        else if ( std::tolower(data.second_button) == "rshift"  ) second_button = VK_RSHIFT  ;
        else if ( std::tolower(data.second_button) == "rcontrol") second_button = VK_RCONTROL;
    }
    
    // Отслеживание клавиш
    while (true) {

        // CNTRL+HOME скриншот
        if (GetAsyncKeyState(first_button)) 
        {
            if (GetAsyncKeyState(second_button)) 
            {
                std::thread th(make_screenshot, std::move( data ));
                th.join();
                mciSendString("play this_play_when_screen.mp3", NULL, 0, NULL);
                Sleep(200);
            }
        }

        // CNTRL+RSHIFT выход из программы
        if (GetAsyncKeyState(first_button)) 
        {
            if (GetAsyncKeyState(VK_F5)) 
            {
                mciSendString("play this_play_when_exit.mp3", NULL, 0, NULL);
                Sleep(1'000);
                break;
            }
        }
        Sleep(500);
    }
    return 0;
}
