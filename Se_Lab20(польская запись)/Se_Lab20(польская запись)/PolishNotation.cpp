#include "stdafx.h"
#include "PolishNotation.h"
#include <stack>
#include <vector>
#include <string>
#include <cstdio>

static int Priority ( const LT::Entry& e )
{
	switch ( e.lexema[0] ) {
		case LEX_LEFTHESIS:  return 0;
		case LEX_RiGHTHESIS: return 0;
		case LEX_COMMA:      return 1;
		case LEX_PLUS:
			if ( e.op == '+' || e.op == '-' ) return 2;
			if ( e.op == '*' || e.op == '/' ) return 3;
			return -1;
		default:
			return -1;
	}
}

static bool IsOperator ( const LT::Entry& e )
{
	return e.lexema[0] == LEX_PLUS &&
		(e.op == '+' || e.op == '-' ||
			e.op == '*' || e.op == '/');
}

static std::string LexToStr ( const LT::Entry& e, IT::IdTable& idtable )
{
	char buf[64];
	switch ( e.lexema[0] ) {
		case LEX_ID:
			if ( e.idxTI != (int)LT_TI_NULLIDX && e.idxTI < idtable.size )
				return std::string ( idtable.table[e.idxTI].id );
			return "?id?";
		case LEX_LITERAL:
			if ( e.idxTI != (int)LT_TI_NULLIDX && e.idxTI < idtable.size ) {
				IT::Entry& ie = idtable.table[e.idxTI];
				if ( ie.iddatatype == IT::INT ) {
					snprintf ( buf, sizeof ( buf ), "%d", ie.value.vint );
					return std::string ( buf );
				}
				return std::string ( "'" ) + std::string ( ie.value.vstr.str, ie.value.vstr.len ) + "'";
			}
			return "?lit?";
		case LEX_PLUS:      return std::string ( 1, e.op );   // + - * /
		case LEX_ASSIGN:    return "=";
		case LEX_LEFTHESIS: return "(";
		case LEX_RiGHTHESIS:return ")";
		case LEX_COMMA:     return ",";
		case LEX_SEMICOLON: return ";";
		case '@':
			snprintf ( buf, sizeof ( buf ), "@%d", (int)(unsigned char)e.op );
			return std::string ( buf );
		default:
			buf[0] = e.lexema[0]; buf[1] = 0;
			return std::string ( buf );
	}
}

bool PolishNotation (
	int lexTable_pos,
	LT::LexTable& lexTable,
	IT::IdTable& idtable )
{
	if ( lexTable_pos < 0 || lexTable_pos >= lexTable.size )
		return false;

	std::vector<LT::Entry> out;
	std::stack<LT::Entry>  st;
	std::stack<int>        args;

	int i = lexTable_pos;

	while ( i < lexTable.size ) {
		LT::Entry e = lexTable.table[i];
		char lex = e.lexema[0];

		if ( lex == LEX_SEMICOLON ) break;

		if ( lex == LEX_ID || lex == LEX_LITERAL ) {
			bool isCall = false;
			if ( lex == LEX_ID &&
				e.idxTI != (int)LT_TI_NULLIDX && e.idxTI < idtable.size &&
				idtable.table[e.idxTI].idtype == IT::F ) {
				if ( i + 1 < lexTable.size &&
					lexTable.table[i + 1].lexema[0] == LEX_LEFTHESIS )
					isCall = true;
			}

			if ( isCall ) {
				st.push ( e );

				LT::Entry paren = lexTable.table[i + 1];
				paren.op = '@';
				st.push ( paren );

				args.push ( 0 );
				i += 2;
				continue;
			}

			out.push_back ( e );
			i++;
			continue;
		}

		if ( lex == LEX_LEFTHESIS ) {
			st.push ( e );
			args.push ( -1 );
			i++;
			continue;
		}

		if ( lex == LEX_RiGHTHESIS ) {
			while ( !st.empty ( ) && st.top ( ).lexema[0] != LEX_LEFTHESIS ) {
				out.push_back ( st.top ( ) );
				st.pop ( );
			}
			if ( st.empty ( ) ) return false;

			LT::Entry paren = st.top ( );
			st.pop ( );

			int cnt = 0;
			if ( !args.empty ( ) ) { cnt = args.top ( ); args.pop ( ); }

			if ( paren.op == '@' ) {
				if ( st.empty ( ) ) return false;
				LT::Entry func = st.top ( );
				st.pop ( );

				out.push_back ( func );

				LT::Entry at;
				at.lexema[0] = '@';
				at.sn = func.sn;
				at.idxTI = (int)LT_TI_NULLIDX;
				at.op = (char)(cnt + 1);
				out.push_back ( at );
			}
			i++;
			continue;
		}

		if ( lex == LEX_COMMA ) {
			while ( !st.empty ( ) && st.top ( ).lexema[0] != LEX_LEFTHESIS ) {
				out.push_back ( st.top ( ) );
				st.pop ( );
			}
			if ( !args.empty ( ) && args.top ( ) >= 0 )
				args.top ( )++;
			i++;
			continue;
		}

		if ( IsOperator ( e ) ) {
			int p = Priority ( e );
			while ( !st.empty ( ) &&
				st.top ( ).lexema[0] != LEX_LEFTHESIS &&
				st.top ( ).op != '@' &&
				IsOperator ( st.top ( ) ) &&
				Priority ( st.top ( ) ) >= p ) {
				out.push_back ( st.top ( ) );
				st.pop ( );
			}
			st.push ( e );
			i++;
			continue;
		}

		if ( lex == LEX_ASSIGN ) {
			while ( !st.empty ( ) &&
				st.top ( ).lexema[0] != LEX_LEFTHESIS &&
				st.top ( ).op != '@' &&
				IsOperator ( st.top ( ) ) ) {
				out.push_back ( st.top ( ) );
				st.pop ( );
			}
			st.push ( e );
			i++;
			continue;
		}

		return false;
	}

	while ( !st.empty ( ) ) {
		if ( st.top ( ).lexema[0] == LEX_LEFTHESIS )
			return false;
		out.push_back ( st.top ( ) );
		st.pop ( );
	}

	int srcEnd = i;

	int w = lexTable_pos;
	for ( size_t k = 0; k < out.size ( ); k++ )
		lexTable.table[w++] = out[k];

	while ( w < srcEnd ) {
		LT::Entry filler;
		filler.lexema[0] = '@';
		filler.sn = lexTable.table[srcEnd].sn;
		filler.idxTI = (int)LT_TI_NULLIDX;
		filler.op = 0;
		lexTable.table[w++] = filler;
	}

	std::cout << "ÏÎËÈÇ (ïîçèöèÿ " << lexTable_pos << "): ";
	for ( size_t k = 0; k < out.size ( ); k++ )
		std::cout << LexToStr ( out[k], idtable ) << " ";
	std::cout << std::endl;

	return true;
}