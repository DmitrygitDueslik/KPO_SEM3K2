#include "stdafx.h"

namespace Str
{
    static bool IsPunct(unsigned char c)
    {
        return c == ';' || c == ',' || c == '{' || c == '}' ||
            c == '(' || c == ')' || c == '+' || c == '-' ||
            c == '*' || c == '/' || c == '=';
    }

    unsigned char* RemoveExtraSpaces(unsigned char* text, int size, int& outSize)
    {
        unsigned char* result = new unsigned char[size + 1];
        int j = 0;
        bool prevSpace = false;
        bool prevEndl = false;
        bool prevPunct = false;

        for (int i = 0; i < size; i++)
        {
            unsigned char c = text[i];

            if (c == ' ')
            {
                if (!prevSpace && !prevPunct)
                {
                    result[j] = c;
                    j++;
                }
                prevSpace = true;
            }
            else if (c == '|')
            {
                while (j > 0 && result[j - 1] == ' ') j--;

                if (!prevEndl)
                {
                    result[j] = c;
                    j++;
                }
                prevEndl = true;
                prevSpace = false;
                prevPunct = false;
            }
            else if (IsPunct(c))
            {
                while (j > 0 && result[j - 1] == ' ') j--;

                result[j] = c;
                j++;
                prevSpace = false;
                prevEndl = false;
                prevPunct = true;      // после знака пробел тоже не нужен
            }
            else
            {
                result[j] = c;
                j++;
                prevSpace = false;
                prevEndl = false;
                prevPunct = false;
            }
        }

        result[j] = '\0';
        outSize = j;
        return result;
    }
}