#include "stdafx.h"
static char EMPTY[] = "";
static char idScope[TI_MAXSIZE][ID_MAXSIZE];
namespace Lexer
{
	static FST::FST fstInteger ( EMPTY, 8,
		FST::NODE ( 1, FST::RELATION ( 'i', 1 ) ),
		FST::NODE ( 1, FST::RELATION ( 'n', 2 ) ),
		FST::NODE ( 1, FST::RELATION ( 't', 3 ) ),
		FST::NODE ( 1, FST::RELATION ( 'e', 4 ) ),
		FST::NODE ( 1, FST::RELATION ( 'g', 5 ) ),
		FST::NODE ( 1, FST::RELATION ( 'e', 6 ) ),
		FST::NODE ( 1, FST::RELATION ( 'r', 7 ) ),
		FST::NODE ( )
	);

	static FST::FST fstString ( EMPTY, 7,
		FST::NODE ( 1, FST::RELATION ( 's', 1 ) ),
		FST::NODE ( 1, FST::RELATION ( 't', 2 ) ),
		FST::NODE ( 1, FST::RELATION ( 'r', 3 ) ),
		FST::NODE ( 1, FST::RELATION ( 'i', 4 ) ),
		FST::NODE ( 1, FST::RELATION ( 'n', 5 ) ),
		FST::NODE ( 1, FST::RELATION ( 'g', 6 ) ),
		FST::NODE ( )
	);

	static FST::FST fstFunction ( EMPTY, 9,
		FST::NODE ( 1, FST::RELATION ( 'f', 1 ) ),
		FST::NODE ( 1, FST::RELATION ( 'u', 2 ) ),
		FST::NODE ( 1, FST::RELATION ( 'n', 3 ) ),
		FST::NODE ( 1, FST::RELATION ( 'c', 4 ) ),
		FST::NODE ( 1, FST::RELATION ( 't', 5 ) ),
		FST::NODE ( 1, FST::RELATION ( 'i', 6 ) ),
		FST::NODE ( 1, FST::RELATION ( 'o', 7 ) ),
		FST::NODE ( 1, FST::RELATION ( 'n', 8 ) ),
		FST::NODE ( )
	);

	static FST::FST fstDeclare ( EMPTY, 8,
		FST::NODE ( 1, FST::RELATION ( 'd', 1 ) ),
		FST::NODE ( 1, FST::RELATION ( 'e', 2 ) ),
		FST::NODE ( 1, FST::RELATION ( 'c', 3 ) ),
		FST::NODE ( 1, FST::RELATION ( 'l', 4 ) ),
		FST::NODE ( 1, FST::RELATION ( 'a', 5 ) ),
		FST::NODE ( 1, FST::RELATION ( 'r', 6 ) ),
		FST::NODE ( 1, FST::RELATION ( 'e', 7 ) ),
		FST::NODE ( )
	);

	static FST::FST fstReturn ( EMPTY, 7,
		FST::NODE ( 1, FST::RELATION ( 'r', 1 ) ),
		FST::NODE ( 1, FST::RELATION ( 'e', 2 ) ),
		FST::NODE ( 1, FST::RELATION ( 't', 3 ) ),
		FST::NODE ( 1, FST::RELATION ( 'u', 4 ) ),
		FST::NODE ( 1, FST::RELATION ( 'r', 5 ) ),
		FST::NODE ( 1, FST::RELATION ( 'n', 6 ) ),
		FST::NODE ( )
	);

	static FST::FST fstPrint ( EMPTY, 6,
		FST::NODE ( 1, FST::RELATION ( 'p', 1 ) ),
		FST::NODE ( 1, FST::RELATION ( 'r', 2 ) ),
		FST::NODE ( 1, FST::RELATION ( 'i', 3 ) ),
		FST::NODE ( 1, FST::RELATION ( 'n', 4 ) ),
		FST::NODE ( 1, FST::RELATION ( 't', 5 ) ),
		FST::NODE ( )
	);

	static FST::FST fstMain ( EMPTY, 5,
		FST::NODE ( 1, FST::RELATION ( 'm', 1 ) ),
		FST::NODE ( 1, FST::RELATION ( 'a', 2 ) ),
		FST::NODE ( 1, FST::RELATION ( 'i', 3 ) ),
		FST::NODE ( 1, FST::RELATION ( 'n', 4 ) ),
		FST::NODE ( )
	);

	// идентификатор: одна или более строчных букв
	static FST::FST fstIdentifier ( EMPTY, 2,
		FST::NODE ( 52,
			FST::RELATION ( 'a', 0 ), FST::RELATION ( 'b', 0 ), FST::RELATION ( 'c', 0 ), FST::RELATION ( 'd', 0 ),
			FST::RELATION ( 'e', 0 ), FST::RELATION ( 'f', 0 ), FST::RELATION ( 'g', 0 ), FST::RELATION ( 'h', 0 ),
			FST::RELATION ( 'i', 0 ), FST::RELATION ( 'j', 0 ), FST::RELATION ( 'k', 0 ), FST::RELATION ( 'l', 0 ),
			FST::RELATION ( 'm', 0 ), FST::RELATION ( 'n', 0 ), FST::RELATION ( 'o', 0 ), FST::RELATION ( 'p', 0 ),
			FST::RELATION ( 'q', 0 ), FST::RELATION ( 'r', 0 ), FST::RELATION ( 's', 0 ), FST::RELATION ( 't', 0 ),
			FST::RELATION ( 'u', 0 ), FST::RELATION ( 'v', 0 ), FST::RELATION ( 'w', 0 ), FST::RELATION ( 'x', 0 ),
			FST::RELATION ( 'y', 0 ), FST::RELATION ( 'z', 0 ),
			FST::RELATION ( 'a', 1 ), FST::RELATION ( 'b', 1 ), FST::RELATION ( 'c', 1 ), FST::RELATION ( 'd', 1 ),
			FST::RELATION ( 'e', 1 ), FST::RELATION ( 'f', 1 ), FST::RELATION ( 'g', 1 ), FST::RELATION ( 'h', 1 ),
			FST::RELATION ( 'i', 1 ), FST::RELATION ( 'j', 1 ), FST::RELATION ( 'k', 1 ), FST::RELATION ( 'l', 1 ),
			FST::RELATION ( 'm', 1 ), FST::RELATION ( 'n', 1 ), FST::RELATION ( 'o', 1 ), FST::RELATION ( 'p', 1 ),
			FST::RELATION ( 'q', 1 ), FST::RELATION ( 'r', 1 ), FST::RELATION ( 's', 1 ), FST::RELATION ( 't', 1 ),
			FST::RELATION ( 'u', 1 ), FST::RELATION ( 'v', 1 ), FST::RELATION ( 'w', 1 ), FST::RELATION ( 'x', 1 ),
			FST::RELATION ( 'y', 1 ), FST::RELATION ( 'z', 1 )
		),
		FST::NODE ( )
	);

	static FST::FST fstNumber ( EMPTY, 2,
		FST::NODE ( 20,
			FST::RELATION ( '0', 0 ), FST::RELATION ( '1', 0 ), FST::RELATION ( '2', 0 ), FST::RELATION ( '3', 0 ),
			FST::RELATION ( '4', 0 ), FST::RELATION ( '5', 0 ), FST::RELATION ( '6', 0 ), FST::RELATION ( '7', 0 ),
			FST::RELATION ( '8', 0 ), FST::RELATION ( '9', 0 ),
			FST::RELATION ( '0', 1 ), FST::RELATION ( '1', 1 ), FST::RELATION ( '2', 1 ), FST::RELATION ( '3', 1 ),
			FST::RELATION ( '4', 1 ), FST::RELATION ( '5', 1 ), FST::RELATION ( '6', 1 ), FST::RELATION ( '7', 1 ),
			FST::RELATION ( '8', 1 ), FST::RELATION ( '9', 1 )
		),
		FST::NODE ( )
	);

	struct SymbolEntry
	{
		char symbol;
		char code;
	};

	static const SymbolEntry SYMBOLS[] =
	{
		{ ';', LEX_SEMICOLON },
		{ ',', LEX_COMMA },
		{ '{', LEX_LEFTBRACE },
		{ '}', LEX_BRACELET },
		{ '(', LEX_LEFTHESIS },
		{ ')', LEX_RiGHTHESIS },
		{ '+', LEX_PLUS },
		{ '-', LEX_MINUS },
		{ '*', LEX_STAR },
		{ '/', LEX_DIRSLASH },
		{ '=', LEX_ASSIGN }
	};
	static const int SYMBOLS_COUNT = 11;

	static bool check ( char* str, FST::FST fst )
	{
		fst.string = str;
		return FST::execute ( fst );
	}

	static char FindKeyword ( char* word )
	{
		if ( check ( word, fstInteger ) )  return LEX_INTEGER;
		if ( check ( word, fstString ) )   return LEX_STRING;
		if ( check ( word, fstFunction ) ) return LEX_FUNCTION;
		if ( check ( word, fstDeclare ) )  return LEX_DECLARE;
		if ( check ( word, fstReturn ) )   return LEX_RETURN;
		if ( check ( word, fstPrint ) )    return LEX_PRINT;
		if ( check ( word, fstMain ) )     return LEX_MAIN;

		return 0;   // значит идентификатор
	}

	static char FindSymbol ( char* token )
	{
		for ( int k = 0; k < SYMBOLS_COUNT; k++ ) {
			FST::FST fst ( token, 2,
				FST::NODE ( 1, FST::RELATION ( SYMBOLS[k].symbol, 1 ) ),
				FST::NODE ( )
			);
			if ( FST::execute ( fst ) )
				return SYMBOLS[k].code;
		}
		return 0;
	}

	static int FindId ( IT::IdTable& it, char id[ID_MAXSIZE], char scope[ID_MAXSIZE] )
	{
		for ( int i = 0; i < it.size; i++ ) {
			if ( it.table[i].idtype == IT::L ) continue;   // литералы не ищем
			if ( strncmp ( it.table[i].id, id, ID_MAXSIZE ) == 0 &&
				strncmp ( idScope[i], scope, ID_MAXSIZE ) == 0 )
				return i;
		}
		return (int)TI_NULLIDX;
	}
	//  лексический анализ

	void Scan ( unsigned char* text, int size, LT::LexTable& lt, IT::IdTable& it )
	{
		int i = 0;
		int line = 1;
		int lineStart = 0;

		char prevWord[300] = "";
		char prevWord2[300] = "";
		char scope[ID_MAXSIZE] = {};
		char paramScope[ID_MAXSIZE] = {};
		bool isDeclare = false;
		bool expectParams = false;
		bool inParams = false;
		while ( i < size ) {
			unsigned char c = text[i];
			int col = i - lineStart + 1;

			//  разделитель строк
			if ( c == '|' ) {
				line++;
				i++;
				lineStart = i;
				continue;
			}

			//  пробел
			if ( c == ' ' ) {
				i++;
				continue;
			}

			//  ключевое слово или идентификатор
			if ( c >= 'a' && c <= 'z' ) {
				char word[300];
				int len = 0;
				while ( i < size && text[i] >= 'a' && text[i] <= 'z' ) {
					if ( len < 299 ) word[len] = text[i];
					len++;
					i++;
				}
				word[(len < 299) ? len : 299] = '\0';

				char kwCode = FindKeyword ( word );

				if ( kwCode != 0 ) {
					// ключевое слово
					LT::Entry entry;
					entry.lexema[0] = kwCode;
					entry.sn = line;
					entry.idxTI = (int)LT_TI_NULLIDX;

					if ( lt.size >= lt.maxsize ) throw ERROR_THROW_IN ( 125, line, col );
					LT::Add ( lt, entry );
					if ( kwCode == LEX_DECLARE ) isDeclare = true;
					if ( kwCode == LEX_MAIN ) {
						memset ( scope, 0, ID_MAXSIZE );
						memcpy ( scope, "main", 4 );
					}
				}
				else if ( check ( word, fstIdentifier ) ) {
					int idLen = (len > ID_MAXSIZE) ? ID_MAXSIZE : len;
					char id[ID_MAXSIZE];
					memset ( id, 0, ID_MAXSIZE );
					memcpy ( id, word, idLen );

					bool isFunc = (strcmp ( prevWord, "function" ) == 0);   // это им€ функции

					// область: у функции пуста€, у параметра его функци€,
					// у остальных функци€, в которой находимс€
					char prefix[ID_MAXSIZE];
					memset ( prefix, 0, ID_MAXSIZE );
					if ( !isFunc )
						memcpy ( prefix, inParams ? paramScope : scope, ID_MAXSIZE );

					int idx = FindId ( it, id, prefix );         // ищем в своей области
					if ( idx == (int)TI_NULLIDX && !isFunc ) {
						char global[ID_MAXSIZE] = {};
						idx = FindId ( it, id, global );         // не нашли - ищем среди функций
					}

					if ( idx == (int)TI_NULLIDX ) {
						IT::Entry ie;
						ie.idxfirstLE = lt.size;
						memset ( ie.id, 0, ID_MAXSIZE );
						memcpy ( ie.id, id, ID_MAXSIZE );

						if ( isFunc )
							ie.idtype = IT::F;                      // им€ функции
						else if ( strcmp ( prevWord2, "declare" ) == 0 )
							ie.idtype = IT::V;                      // объ€вление переменной
						else if ( strcmp ( prevWord, "integer" ) == 0 || strcmp ( prevWord, "string" ) == 0 )
							ie.idtype = IT::P;                      // параметр функции
						else
							ie.idtype = IT::V;

						if ( strcmp ( prevWord, "string" ) == 0 || strcmp ( prevWord2, "string" ) == 0 )
							ie.iddatatype = IT::STR;
						else
							ie.iddatatype = IT::INT;

						ie.value.vint = TI_INT_DEFAULT;

						if ( it.size >= it.maxsize ) throw ERROR_THROW_IN ( 126, line, col );
						IT::Add ( it, ie );
						idx = it.size - 1;
						memcpy ( idScope[idx], prefix, ID_MAXSIZE );   // запоминаем область
					}

					if ( isFunc ) {
						memcpy ( paramScope, id, ID_MAXSIZE );   // параметры получат им€ этой функции
						expectParams = true;
						if ( !isDeclare )
							memcpy ( scope, id, ID_MAXSIZE );    // это определение - дальше еЄ тело
					}

					LT::Entry entry;
					entry.lexema[0] = LEX_ID;
					entry.sn = line;
					entry.idxTI = idx;

					if ( lt.size >= lt.maxsize ) throw ERROR_THROW_IN ( 125, line, col );
					LT::Add ( lt, entry );
				}
				else {
					throw ERROR_THROW_IN ( 120, line, col );
				}

				// запоминаем два последних слова дл€ следующей итерации
				strcpy_s ( prevWord2, prevWord );
				strcpy_s ( prevWord, word );

				continue;
			}

			//  целочисленный литерал
			if ( c >= '0' && c <= '9' ) {
				char digits[300];
				int len = 0;
				while ( i < size && text[i] >= '0' && text[i] <= '9' ) {
					if ( len < 299 ) digits[len] = text[i];
					len++;
					i++;
				}
				digits[(len < 299) ? len : 299] = '\0';

				if ( !check ( digits, fstNumber ) ) throw ERROR_THROW_IN ( 124, line, col );
				if ( len > 10 ) throw ERROR_THROW_IN ( 123, line, col );

				long value = atol ( digits );
				if ( value > 2147483647L ) throw ERROR_THROW_IN ( 123, line, col );

				IT::Entry ie;
				ie.idxfirstLE = lt.size;
				memset ( ie.id, 0, ID_MAXSIZE );
				strcpy_s ( ie.id, "lit" );
				ie.iddatatype = IT::INT;
				ie.idtype = IT::L;
				ie.value.vint = (int)value;

				if ( it.size >= it.maxsize ) throw ERROR_THROW_IN ( 126, line, col );
				IT::Add ( it, ie );
				int idx = it.size - 1;

				LT::Entry entry;
				entry.lexema[0] = LEX_LITERAL;
				entry.sn = line;
				entry.idxTI = idx;

				if ( lt.size >= lt.maxsize ) throw ERROR_THROW_IN ( 125, line, col );
				LT::Add ( lt, entry );

				continue;
			}

			//  строковый литерал
			if ( c == '\'' ) {
				i++;                          // пропуск открывающего апострофа
				char str[TI_STR_MAXSIZE];
				int len = 0;
				bool closed = false;

				while ( i < size ) {
					if ( text[i] == '\'' ) {
						closed = true;
						i++;
						break;
					}
					if ( text[i] == '|' ) {
						break;                // строка не может переходить на новую строку
					}
					if ( len < TI_STR_MAXSIZE - 1 ) str[len] = text[i];
					len++;
					i++;
				}

				if ( !closed ) throw ERROR_THROW_IN ( 121, line, col );
				if ( len > TI_STR_MAXSIZE - 1 ) throw ERROR_THROW_IN ( 122, line, col );

				IT::Entry ie;
				ie.idxfirstLE = lt.size;
				memset ( ie.id, 0, ID_MAXSIZE );
				strcpy_s ( ie.id, "str" );
				ie.iddatatype = IT::STR;
				ie.idtype = IT::L;
				ie.value.vstr.len = (char)len;
				memcpy ( ie.value.vstr.str, str, len );

				if ( it.size >= it.maxsize ) throw ERROR_THROW_IN ( 126, line, col );
				IT::Add ( it, ie );
				int idx = it.size - 1;

				LT::Entry entry;
				entry.lexema[0] = LEX_LITERAL;
				entry.sn = line;
				entry.idxTI = idx;

				if ( lt.size >= lt.maxsize ) throw ERROR_THROW_IN ( 125, line, col );
				LT::Add ( lt, entry );

				continue;
			}

			//  пунктуаци€ и операции
			char token[2];
			token[0] = c;
			token[1] = '\0';

			char code = FindSymbol ( token );

			if ( code != 0 ) {
				LT::Entry entry;
				entry.lexema[0] = code;
				entry.sn = line;
				entry.idxTI = (int)LT_TI_NULLIDX;

				if ( lt.size >= lt.maxsize ) throw ERROR_THROW_IN ( 125, line, col );
				LT::Add ( lt, entry );
				if ( code == LEX_LEFTHESIS && expectParams ) inParams = true;   // началс€ список параметров
				if ( code == LEX_RiGHTHESIS ) inParams = false;                 // закончилс€
				if ( code == LEX_SEMICOLON )  isDeclare = false;                // конец инструкции
				expectParams = false;
				i++;
				continue;
			}

			//  символ не подошЄл ни под одно правило
			throw ERROR_THROW_IN ( 124, line, col );
		}
	}
}