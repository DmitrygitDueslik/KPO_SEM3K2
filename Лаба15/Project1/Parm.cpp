#include "Parm.h"
#include "Error.h"
#include <cstring>
#include <cwchar>
#include <stdlib.h>

namespace Parm
{
    PARM getparm(int argc, char* argv[])
    {
        PARM parm;

        // Инициализируем пустыми строками
        parm.in[0] = L'\0';
        parm.out[0] = L'\0';
        parm.log[0] = L'\0';

        bool foundIn = false;

        for (int i = 1; i < argc; i++)
        {
            // Конвертируем argv[i] из char* в wchar_t
            wchar_t arg[PARM_MAX_SIZE];
            size_t converted = 0;
            mbstowcs_s(&converted, arg, PARM_MAX_SIZE, argv[i], _TRUNCATE);

            // Проверяем длину
            if (wcslen(arg) >= PARM_MAX_SIZE)
            {
                throw ERROR_THROW(104);
            }

            // Проверяем ключ -in:
            if (wcsstr(arg, PARM_IN) == arg)
            {
                foundIn = true;
                wcscpy_s(parm.in, arg + wcslen(PARM_IN));
            }
            // Проверяем ключ -out:
            else if (wcsstr(arg, PARM_OUT) == arg)
            {
                wcscpy_s(parm.out, arg + wcslen(PARM_OUT));
            }
            // Проверяем ключ -log:
            else if (wcsstr(arg, PARM_LOG) == arg)
            {
                wcscpy_s(parm.log, arg + wcslen(PARM_LOG));
            }
        }

        // Если -in не задан щшибка 100
        if (!foundIn)
        {
            throw ERROR_THROW(100);
        }

        // Формируем значения по умолчанию для -out
        if (wcslen(parm.out) == 0)
        {
            wcscpy_s(parm.out, parm.in);
            wcsncat_s(parm.out, PARM_OUT_DEFAULT_EXT, _TRUNCATE);
        }

        // Формируем значения  для -log
        if (wcslen(parm.log) == 0)  
        {
            wcscpy_s(parm.log, parm.in);
            wcsncat_s(parm.log,L".log" PARM_LOG_DEFAULT_EXT, _TRUNCATE);

        }

        return parm;
    }
}