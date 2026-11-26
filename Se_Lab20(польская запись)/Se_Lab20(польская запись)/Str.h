#pragma once
namespace Str { 
	// ”бирает несколько подр€д идущих пробелов, оставл€€ один.
	// —имвол '|' (бывший перевод строки) никак не трогаем - он уже
	// играет роль сепаратора строк дл€ подсчЄта номера строки лексемы.
	unsigned char* RemoveExtraSpaces(unsigned char* text, int size, int& outSize);
}