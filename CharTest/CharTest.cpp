// CharTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////
//  控制台窗口设置信息

typedef enum _CONSOLE_SCREEN_INFO {   
    ConsoleScreenRight  = 150,                      //  窗口宽度
    ConsoleScreenBottom = 30,                       //  窗口高度
    ConsoleScreenBuffer = 5000                      //  缓冲区高度
} CONSOLE_SCREEN_INFO; 

#define RUN_INFO	FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define WARN_INFO	FOREGROUND_BLUE  | FOREGROUND_INTENSITY	
#define ERROE_INFO	FOREGROUND_RED   | FOREGROUND_INTENSITY	

////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------//
// 设置当前控制台窗口大小和背景色、字体颜色等                       //
//------------------------------------------------------------------//
VOID
WINAPI
SetCurrConsoleWindowStatus(
IN HANDLE hConsoleOutput,
IN WORD wAttributes
){
    COORD BufferSize = {0};
    SMALL_RECT WindowSize ={0};

    BufferSize.X = ConsoleScreenRight;
    BufferSize.Y = ConsoleScreenBuffer;
    WindowSize.Right  = ConsoleScreenRight - 1;
    WindowSize.Bottom = ConsoleScreenBottom - 1;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);           //	设置字体颜色为高亮的绿色，背景色为黑色
    SetConsoleScreenBufferSize(hConsoleOutput, BufferSize);         //	必须要先调整缓冲区大小
    SetConsoleWindowInfo(hConsoleOutput, TRUE, &WindowSize);        //	再调整窗口大小才行，不然没有效果
}

typedef struct _CMD_TASK_PKG_HEAD {
    DWORD64 nDataSize;
    PBYTE  pPkgData;
    SIZE_T nPkgSize;
} CMD_TASK_PKG_HEAD, *PCMD_TASK_PKG_HEAD, *LPCMD_TASK_PKG_HEAD;

VOID WINAPI FuncA(IN VOID)
{
    unsigned char ch [0x100];

    for (int i = 0; i < 0x100; i++)
        ch[i] = i;

    printf("\r\n\n 二进制表的处理  无符号的char \n");

    for (int i = 0; i < 0x100; i++)
    {
        printf(" %02X", ch[i]);

        if (0 == i)
            continue;

        if (0 == ((i + 1) & 7))
            printf(" ");

        if (0 == ((i + 1) & 15))
            printf("\r\n");
    }
}

VOID WINAPI FuncB(IN VOID)
{
    char ch [0x100];

    for (int i = 0; i < 0x100; i++)
        ch[i] = i;

    printf("\r\n\n 二进制表的处理  有符号的char \n");

    for (int i = 0; i < 0x100; i++)
    {
        printf(" %02X", ch[i]);

        if (0 == i)
            continue;

        if (0 == ((i + 1) & 7))
            printf(" ");

        if (0 == ((i + 1) & 15))
            printf("\r\n");
    }
}

VOID WINAPI FuncC(IN VOID)
{
    LPSTR  lpStr = "Abcdefg";
    SIZE_T nLen  = strlen(lpStr) - 1;

    //  当某些时候，需要特殊处理，反着复制的时候

    printf("\r\n\r\n\r\n 循环变量为 int(无符号) 的时候 \n");

    for (INT nPos = (INT)nLen; nPos >= 0; nPos--)        
    {
        printf(" %c", lpStr[nPos]);
    }

    printf("\r\n\r\n\r\n 循环变量为 SIZE_T(无符号) 的时候 \n");

    for (SIZE_T nPos = nLen, i = 0; nPos >= 0; nPos--, i++)
    {
        printf(" %c", lpStr[nPos]);

        if (100 == i)
            break;
    }
}

int _tmain(int argc, _TCHAR* argv[])
{
    SetCurrConsoleWindowStatus(GetStdHandle(STD_OUTPUT_HANDLE), RUN_INFO);

    FuncA();
    FuncB();

    FuncC();


    getchar();

	return 0;
}
