#include "stdafx.h"


namespace In
{
    IN getin(wchar_t* infile)
    {
        IN in;
        in.size = 0;
        in.lines = 0;
        in.ignor = 0;

        int codeTable[] = IN_CODE_TABLE;
        for (int i = 0; i < 256; i++)
        {
            in.code[i] = codeTable[i];
        }

        // Конвертируем wchar_t* в char* для ifstream
        char filename[1024];
        size_t converted = 0;
        wcstombs_s(&converted, filename, 1024, infile, _TRUNCATE);

        // Открываем файл в бинарном режиме
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open())
        {
            throw ERROR_THROW(110);
        }

        // Выделяем память для текста
        in.text = new unsigned char[IN_MAX_LEN_TEXT];

        // Инициализируем нулями
        for (int i = 0; i < IN_MAX_LEN_TEXT; i++) {
            in.text[i] = 0;
        }

        int pos = 0;
        int line = 1;
        int col = 1;

        bool sawAnyChar = false;   // был ли вообще хоть один символ в файле
        bool lastWasEndl = false;  // был ли последний обработанный символ переводом строки


        char ch;
        while (file.get(ch))
        {
            unsigned char uch = (unsigned char)ch;
            int code = in.code[uch];

            sawAnyChar = true;
            if (code == IN::F)
            {
                // Запрещённый символ  ошибка 111
                delete[] in.text;
                file.close();
                throw ERROR_THROW_IN(111, line, col);
            }
            else if (code == IN::I)
            {
                // Игнорируемый символ не пишем, просто считаем
                in.ignor++;
            }
            else if (code == IN::T)
            {
                // Разрешённый символ вводим как было
                in.text[pos] = uch;
                pos++;
                in.size++;
            }
            else
            {
                // Замена символа (code от 0 до 255)
                in.text[pos] = (unsigned char)code;
                pos++;
                in.size++;
            }


            if (uch == IN_CODE_ENDL)
            {
                in.lines++;
                line++;
                col = 1;
                lastWasEndl = true;

            }
            else
            {
                col++;
                lastWasEndl = false;

            }
        }
        //Для подсчета строки если не заканчивается на \n
        if (sawAnyChar && !lastWasEndl)
        {
            in.lines++;
        }

        file.close();
        return in;
    }
}