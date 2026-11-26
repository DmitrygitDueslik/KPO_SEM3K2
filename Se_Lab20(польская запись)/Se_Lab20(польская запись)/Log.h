#pragma once
#include "stdafx.h"



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
    void WriteLT(LOG& log, LT::LexTable& lt);
    void WriteIT(LOG& log, IT::IdTable& it);
    void WriteLog(LOG& log);
    void WriteParm(LOG& log, Parm::PARM& parm);
    void WriteIn(LOG& log, In::IN& in);
    void WriteError(LOG& log, Error::ERROR& err);
    void Close(LOG& log);
}