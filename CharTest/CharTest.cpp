// CharTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////////
//  ����̨����������Ϣ

typedef enum _CONSOLE_SCREEN_INFO {   
    ConsoleScreenRight  = 150,                      //  ���ڿ��
    ConsoleScreenBottom = 30,                       //  ���ڸ߶�
    ConsoleScreenBuffer = 5000                      //  �������߶�
} CONSOLE_SCREEN_INFO; 

#define RUN_INFO	FOREGROUND_GREEN | FOREGROUND_INTENSITY
#define WARN_INFO	FOREGROUND_BLUE  | FOREGROUND_INTENSITY	
#define ERROE_INFO	FOREGROUND_RED   | FOREGROUND_INTENSITY	

////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------//
// ���õ�ǰ����̨���ڴ�С�ͱ���ɫ��������ɫ��                       //
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

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);           //	����������ɫΪ��������ɫ������ɫΪ��ɫ
    SetConsoleScreenBufferSize(hConsoleOutput, BufferSize);         //	����Ҫ�ȵ�����������С
    SetConsoleWindowInfo(hConsoleOutput, TRUE, &WindowSize);        //	�ٵ������ڴ�С���У���Ȼû��Ч��
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

    printf("\r\n\n �����Ʊ�Ĵ���  �޷��ŵ�char \n");

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

    printf("\r\n\n �����Ʊ�Ĵ���  �з��ŵ�char \n");

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

    //  ��ĳЩʱ����Ҫ���⴦�����Ÿ��Ƶ�ʱ��

    printf("\r\n\r\n\r\n ѭ������Ϊ int(�޷���) ��ʱ�� \n");

    for (INT nPos = (INT)nLen; nPos >= 0; nPos--)        
    {
        printf(" %c", lpStr[nPos]);
    }

    printf("\r\n\r\n\r\n ѭ������Ϊ SIZE_T(�޷���) ��ʱ�� \n");

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
