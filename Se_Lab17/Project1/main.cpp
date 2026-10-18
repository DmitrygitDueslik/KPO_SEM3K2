#include "stdafx.h"


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");

  

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

        int cleanSize = 0;
        unsigned char* cleanText = Str::RemoveExtraSpaces(in.text, in.size, cleanSize);

        std::cout << cleanText << std::endl;
        std::cout << "Всего символов: " << cleanSize << std::endl;
        std::cout << "Всего строк: " << in.lines << std::endl;
        std::cout << "Пропущено: " << in.ignor << std::endl;

        // 4. ЗАПИСЬ ФАЙЛА .out 
        std::ofstream outFile(parm.out, std::ios::binary);
        if (!outFile.is_open())
        {
            throw ERROR_THROW(110);
        }
        outFile.write(reinterpret_cast<const char*>(cleanText), cleanSize);
        outFile.close();

        // 5. Лексический анализ
        LT::LexTable lt = LT::Create(LT_MAXSIZE);
        IT::IdTable it = IT::Create(TI_MAXSIZE);

        Lexer::Scan(cleanText, cleanSize, lt, it);

        std::cout << std::endl << "Лексический анализ завершён." << std::endl;
        std::cout << "Лексем найдено: " << lt.size << std::endl;
        std::cout << "Идентификаторов найдено: " << it.size << std::endl;

        Log::WriteLT(log, lt);
        Log::WriteIT(log, it);

        LT::Delete(lt);
        IT::Delete(it);

        delete[] cleanText;
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