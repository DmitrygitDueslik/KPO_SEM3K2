#pragma once

#define IN_MAX_LEN_TEXT (1024*1024)
#define IN_CODE_ENDL '\n'

//
// Разрешены (T) 
// Всё остальное - IN::I 
#define IN_CODE_TABLE { \
/* 0-15   */ IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, '%', IN::I, IN::I, IN::I, IN::I, IN::I, \
/* 16-31  */ IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, \
/* 32-47  */ IN::T, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, \
/* 48-63  */ IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, \
/* 64-79  */ IN::I, IN::I, IN::I, IN::I, IN::T, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::T, IN::I, \
/* 80-95  */ IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::T, IN::I, IN::I, IN::I, IN::I, IN::I, \
/* 96-111 */ IN::I, IN::T, IN::I, IN::T, IN::I, IN::T, IN::I, IN::I, IN::T, IN::T, IN::I, IN::T, IN::T, IN::T, IN::T, IN::T, \
/* 112-127*/ IN::I, IN::I, IN::T, IN::I, IN::T, IN::I, IN::T, IN::I, IN::I, IN::T, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, \
/* 128-143*/ IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, \
/* 144-159*/ IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, \
/* 160-175*/ IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, \
/* 176-191*/ IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, \
/* 192-207*/ IN::I, IN::I, IN::I, IN::I, IN::T, IN::I, IN::I, IN::T, IN::I, IN::I, IN::I, IN::I, IN::I, IN::T, IN::I, IN::I, \
/* 208-223*/ IN::I, IN::I, IN::F, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, IN::I, \
/* 224-239*/ IN::T, IN::I, IN::T, IN::I, IN::I, IN::T, IN::I, IN::I, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::I, \
/* 240-255*/ IN::T, IN::I, IN::T, IN::I, IN::I, IN::I, IN::I, IN::T, IN::I, IN::I, IN::I, IN::T, IN::I, IN::I, IN::I, IN::T  \
}

namespace In
{
    struct IN
    {
        enum { T = 1024, F = 2048, I = 4096 };
        int size;
        int lines;
        int ignor;
        unsigned char* text;
        int code[256];
    };

    IN getin(wchar_t* infile);
}