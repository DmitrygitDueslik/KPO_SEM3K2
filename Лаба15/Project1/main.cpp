#include <iostream>
#include <locale>
#include "Error.h"
#include "Parm.h"
#include "In.h"
#include "Log.h"


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");

   //Навсякий для проверки -out в cmd
    //bool outGiven = false;
    //for (int i = 1; i < argc; i++)
    //{
    //    if (strncmp(argv[i], "-out:", 5) == 0)
    //    {
    //        outGiven = true;
    //        break;
    //    }
    //}


    Log::LOG log;
    log.isOpen = false;
	Parm::PARM parm;
    parm.in[0] = L'\0';
	parm.out[0] = L'\0';
	parm.log[0] = L'\0';

    try
    {
        // 1. Обработка параметров
		parm = Parm::getparm(argc, argv);
        // 2. Создание журнала
        log = Log::getlog(parm.log);

        Log::WriteLine(log, (char*)"Тест:", (char*)" без ошибок \n", "");
        Log::WriteLine(log, (wchar_t*)L"Тест:", (wchar_t*)L" без ошибок \n", L"");
        Log::WriteLog(log);
        Log::WriteParm(log, parm);


        // 3. Ввод исходного кода
        In::IN in = In::getin(parm.in);
        Log::WriteIn(log, in);

        std::cout << in.text << std::endl;
        std::cout << "Всего символов: " << in.size << std::endl;
        std::cout << "Всего строк: " << in.lines << std::endl;
        std::cout << "Пропущено: " << in.ignor << std::endl;

        // 4. ЗАПИСЬ ФАЙЛА .out 
        std::ofstream outFile(parm.out, std::ios::binary);
        if (!outFile.is_open())
        {
            throw ERROR_THROW(110);
        }
        outFile.write(reinterpret_cast<const char*>(in.text), in.size);
        outFile.close();

        delete[] in.text;

        Log::Close(log);
    }
    catch (Error::ERROR e)
    {
        Log::WriteError(log, e);
        std::cout << "Ошибка " << e.id << ": " << e.message << std::endl;
        std::cout << "строка " << e.inext.line
            << " позиция " << e.inext.col << std::endl << std::endl;

		if (wcslen(parm.out) > 0)
		{
			std::ofstream outFile(parm.out, std::ios::binary);
			if (outFile.is_open())
			{
				outFile << "Ошибка " << e.id << ": " << e.message;
                if(e.inext.line>=0)
                {
                    outFile << " строка " << e.inext.line << " позиция " << e.inext.col;
                }
				outFile << std::endl;
				outFile.close();
			}
		}
        Log::Close(log);
    }

    system("pause");


    

    return 0;
}