#pragma once
#include "LT.h"
#include "IT.h"

namespace LEX
{
	struct LEX                      // результат работы лексического анализатора
	{
		LT::LexTable lextable;      // таблица лексем
		IT::IdTable  idtable;       // таблица идентификаторов
	};
};