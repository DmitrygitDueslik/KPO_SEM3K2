#pragma once
#include "Error.h"  
#include "Parm.h"
#include "In.h"
#include <fstream>

namespace Log
{
    struct LOG
    {
        std::ofstream stream;
        bool isOpen=false;
    };

    LOG getlog(wchar_t* logfile);
    void WriteLine(LOG& log, const char* str, ...);
    void WriteLine(LOG& log, const wchar_t* str, ...);
    void WriteLog(LOG& log);
    void WriteParm(LOG& log, Parm::PARM& parm);
    void WriteIn(LOG& log, In::IN& in);
    void WriteError(LOG& log, Error::ERROR& err);
    void Close(LOG& log);
}