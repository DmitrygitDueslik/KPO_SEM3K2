#pragma once
#include "stdafx.h"
namespace Lexer {
    //  заполняет таблицу лексем и таблицу идентификаторов.
    void Scan(unsigned char* text, int size, LT::LexTable& lt, IT::IdTable& it);
}
