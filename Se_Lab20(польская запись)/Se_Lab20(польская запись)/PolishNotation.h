#pragma once
#include "stdafx.h"

// lexTable_pos Ч позици€ первого символа выражени€ в таблице лексем.
// –езультат записываетс€ обратно в lexTable с позиции lexTable_pos,
// хвост до конца исходного выражени€ заполн€етс€ символом-заполнителем '@'.
// ¬озвращает true Ч ѕќЋ»« построен, false Ч ошибка.
bool PolishNotation ( int lexTable_pos, LT::LexTable& lexTable, IT::IdTable& idTable );