#include "Log.h"
#include <ctime>
#include <cstdarg>
#include <cstring>
#include <iostream>

namespace Log
{
    LOG getlog(wchar_t* logfile)
    {
        LOG log;

        // Конвертируем wchar_t* в char*
        char filename[1024];
        size_t converted = 0;
        wcstombs_s(&converted, filename, 1024, logfile, _TRUNCATE);

        log.stream.open(filename, std::ios::out | std::ios::trunc);
        if (!log.stream.is_open())
        {
            throw ERROR_THROW(112);
        }
        log.isOpen = true;
        return log;
    }

    void WriteLine(LOG& log, const char* str, ...)
    {
        if (log.isOpen) {
            va_list args;
            va_start(args, str);
            const char* part = str;
            while(part!=nullptr && part[0]!='\0')
                            {
                log.stream << part;
                part = va_arg(args, const char*);
            }
            va_end(args);
            log.stream << std::endl;
            
        }
    }

    void WriteLine(LOG& log, const wchar_t* str, ...)
    {
        if (log.isOpen)
        {
            va_list args;
			va_start(args, str);
            char buffer[1024];
			const wchar_t* part = str;
			while (part != nullptr && part[0] != L'\0')
			{
				size_t converted = 0;
				wcstombs_s(&converted, buffer, 1024, part, _TRUNCATE);
				log.stream << buffer;
				part = va_arg(args, const wchar_t*);
			}
            va_end(args);
            log.stream << std::endl;
            
        }
    }

    void WriteLog(LOG& log)
    {
        if (log.isOpen)
        {
            time_t now = time(0);
            struct tm tstruct;
            localtime_s(&tstruct, &now);
            char buf[80];
            strftime(buf, sizeof(buf), "Протокол от %Y-%m-%d %X", &tstruct);
            log.stream << buf << std::endl;
        }
    }

    void WriteParm(LOG& log, Parm::PARM& parm)
    {
        if (log.isOpen)
        {
            char in[300], out[300], lg[300];
            size_t conv = 0;
            wcstombs_s(&conv, in, 300, parm.in, _TRUNCATE);
            wcstombs_s(&conv, out, 300, parm.out, _TRUNCATE);
            wcstombs_s(&conv, lg, 300, parm.log, _TRUNCATE);
            log.stream << "Параметры:" << std::endl;
            log.stream << "  -in: " << in << std::endl;
            log.stream << "  -out: " << out << std::endl;
            log.stream << "  -log: " << lg << std::endl;
        }
    }

    void WriteIn(LOG& log, In::IN& in)
    {
        if (log.isOpen)
        {
            log.stream << "Входные данные:" << std::endl;
            log.stream << "  Размер: " << in.size << std::endl;
            log.stream << "  Строк: " << in.lines << std::endl;
            log.stream << "  Пропущено: " << in.ignor << std::endl;
        }
    }

    void WriteError(LOG& log, Error::ERROR& err)
    {
        if (log.isOpen)
        {
            log.stream << "Ошибка " << err.id << ": " << err.message;
            if (err.inext.line >= 0)
            {
                log.stream << " (строка " << err.inext.line
                    << ", позиция " << err.inext.col << ")";
            }
            log.stream << std::endl;
        }
        else
        {
            std::cout << "Ошибка " << err.id << ": " << err.message << std::endl;
            if (err.inext.line >= 0)
            {
                std::cout << "Строка: " << err.inext.line
                    << ", Позиция: " << err.inext.col << std::endl;
            }
        }
    }

    void Close(LOG& log)
    {
        if (log.isOpen)
        {
            log.stream.close();
            log.isOpen = false;
        }
    }
}