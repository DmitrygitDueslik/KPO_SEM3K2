#include "stdafx.h"
#include "MFST.h"

int  FST_TRACE_n = -1;                                  // номер шага
char rbuf[205], sbuf[205], lbuf[1024];                  // буферы для печати
#define NS(n)   GRB::Rule::Chain::N(n)
#define TS(n)   GRB::Rule::Chain::T(n)
#define ISNS(n) GRB::Rule::Chain::isN(n)

// шаг с правилом: номер, правило, лента, стек
#define MFST_TRACE1 std::cout << std::setw(4) << std::left << ++FST_TRACE_n << ": " \
	<< std::setw(20) << std::left << rule.getCRule(rbuf, nrulechain)                   \
	<< std::setw(30) << std::left << getCLenta(lbuf, lenta_position)                   \
	<< std::setw(20) << std::left << getCSt(sbuf)                                      \
	<< std::endl;

// состояние после шага (номер шага не меняется)
#define MFST_TRACE2 std::cout << std::setw(4) << std::left << FST_TRACE_n << ": "      \
	<< std::setw(20) << std::left << " "                                               \
	<< std::setw(30) << std::left << getCLenta(lbuf, lenta_position)                   \
	<< std::setw(20) << std::left << getCSt(sbuf)                                      \
	<< std::endl;

// новый шаг без правила (сдвиг ленты)
#define MFST_TRACE3 std::cout << std::setw(4) << std::left << ++FST_TRACE_n << ": "    \
	<< std::setw(20) << std::left << " "                                               \
	<< std::setw(30) << std::left << getCLenta(lbuf, lenta_position)                   \
	<< std::setw(20) << std::left << getCSt(sbuf)                                      \
	<< std::endl;

#define MFST_TRACE4(c)    std::cout << std::setw(4) << std::left << ++FST_TRACE_n << ": " << std::setw(20) << std::left << c << std::endl;
#define MFST_TRACE5(c)    std::cout << std::setw(4) << std::left << FST_TRACE_n << ": "   << std::setw(20) << std::left << c << std::endl;
#define MFST_TRACE6(c, k) std::cout << std::setw(4) << std::left << FST_TRACE_n << ": "   << std::setw(20) << std::left << c << k << std::endl;

namespace MFST
{
	MfstState::MfstState ( )
	{
		lenta_position = 0;
		nrulechain = -1;
	};

	MfstState::MfstState ( short pposition, MFSTSTSTACK pst, short pnrulechain )
	{
		lenta_position = pposition;
		st = pst;
		nrulechain = pnrulechain;
	};

	Mfst::MfstDiagnosis::MfstDiagnosis ( )
	{
		lenta_position = -1;
		rc_step = SURPRISE;
		nrule = -1;
		nrule_chain = -1;
	};

	Mfst::MfstDiagnosis::MfstDiagnosis ( short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain )
	{
		lenta_position = plenta_position;
		rc_step = prc_step;
		nrule = pnrule;
		nrule_chain = pnrule_chain;
	};

	Mfst::Mfst ( ) { lenta = 0; lenta_size = lenta_position = 0; nrule = nrulechain = -1; };

	Mfst::Mfst ( LEX::LEX plex, GRB::Greibach pgrebach )
	{
		grebach = pgrebach;
		lex = plex;
		lenta = new short[lex.lextable.size + 1];
		lenta_size = 0;
		for ( int k = 0; k < lex.lextable.size; k++ )
			lenta[lenta_size++] = TS ( lex.lextable.table[k].lexema[0] );
		if ( lenta_size == 0 || lenta[lenta_size - 1] != grebach.stbottomT )
			lenta[lenta_size++] = grebach.stbottomT;
		lenta_position = 0;
		nrule = -1;
		nrulechain = -1;
		st.push ( grebach.stbottomT );
		st.push ( grebach.startN );
	};

	Mfst::RC_STEP Mfst::step ( )
	{
		RC_STEP rc = SURPRISE;
		if ( lenta_position < lenta_size ) {
			if ( st.empty ( ) ) {
				MFST_TRACE4 ( "TS_NOK/NS_NORULECHAIN" )
					rc = reststate ( ) ? TS_NOK : NS_NORULECHAIN;
			}
			else if ( ISNS ( st.top ( ) ) ) {
				GRB::Rule rule;
				if ( (nrule = grebach.getRule ( st.top ( ), rule )) >= 0 ) {
					GRB::Rule::Chain chain;
					if ( (nrulechain = rule.getNextChain ( lenta[lenta_position], chain, nrulechain + 1 )) >= 0 ) {
						MFST_TRACE1
							savestate ( );
						st.pop ( );
						push_chain ( chain );
						rc = NS_OK;
						MFST_TRACE2
					}
					else {
						MFST_TRACE4 ( "TNS_NORULECHAIN/NS_NORULE" )
							savediagnosis ( NS_NORULECHAIN );
						rc = reststate ( ) ? NS_NORULECHAIN : NS_NORULE;
					};
				}
				else rc = NS_ERROR;
			}
			else if ( st.top ( ) == lenta[lenta_position] ) {
				lenta_position++;
				st.pop ( );
				nrulechain = -1;
				rc = TS_OK;
				MFST_TRACE3
			}
			else { MFST_TRACE4 ( "TS_NOK/NS_NORULECHAIN" ) rc = reststate ( ) ? TS_NOK : NS_NORULECHAIN; };
		}
		else { rc = LENTA_END; MFST_TRACE4 ( "LENTA_END" ) };
		return rc;
	};

	bool Mfst::push_chain ( GRB::Rule::Chain chain )
	{
		for ( int k = chain.size - 1; k >= 0; k-- ) st.push ( chain.nt[k] );
		return true;
	};

	bool Mfst::savestate ( )
	{
		storestate.push ( MfstState ( lenta_position, st, nrulechain ) );
		MFST_TRACE6 ( "SAVESTATE:", storestate.size ( ) );
		return true;
	};

	bool Mfst::reststate ( )
	{
		bool rc = false;
		MfstState state;
		if ( rc = (storestate.size ( ) > 0) ) {
			state = storestate.top ( );
			lenta_position = state.lenta_position;
			st = state.st;
			nrulechain = state.nrulechain;
			storestate.pop ( );
			MFST_TRACE5 ( "RESSTATE" )
				MFST_TRACE2
		};
		return rc;
	};

	bool Mfst::savediagnosis ( RC_STEP prc_step )
	{
		bool rc = false;
		short k = 0;
		while ( k < MFST_DIAGN_NUMBER && lenta_position <= diagnosis[k].lenta_position ) k++;
		if ( rc = (k < MFST_DIAGN_NUMBER) ) {
			diagnosis[k] = MfstDiagnosis ( lenta_position, prc_step, nrule, nrulechain );
			for ( short j = k + 1; j < MFST_DIAGN_NUMBER; j++ ) diagnosis[j].lenta_position = -1;
		};
		return rc;
	};

	// ---------------- запуск автомата ----------------

	bool Mfst::start ( )
	{
		bool rc = false;
		RC_STEP rc_step = SURPRISE;
		char buf[MFST_DIAGN_MAXSIZE];
		FST_TRACE_n = -1;
		rc_step = step ( );
		while ( rc_step == NS_OK || rc_step == NS_NORULECHAIN || rc_step == TS_OK || rc_step == TS_NOK ) rc_step = step ( );

		int lines = (lex.lextable.size > 0) ? lex.lextable.table[lex.lextable.size - 1].sn : 0;

		switch ( rc_step ) {
			case LENTA_END:      MFST_TRACE4 ( "------>LENTA_END" )
				std::cout << "-------------------------------------------------------------------------------------" << std::endl;
				std::cout << std::setw ( 4 ) << std::left << 0 << ": всего строк " << lines << ", синтаксический анализ выполнен без ошибок" << std::endl;
				rc = true;
				break;
			case NS_NORULE:      MFST_TRACE4 ( "------>NS_NORULE" )
				std::cout << "-------------------------------------------------------------------------------------" << std::endl;
				std::cout << getDiagnosis ( 0, buf ) << std::endl;
				std::cout << getDiagnosis ( 1, buf ) << std::endl;
				std::cout << getDiagnosis ( 2, buf ) << std::endl;
				break;
			case NS_NORULECHAIN: MFST_TRACE4 ( "------>NS_NORULECHAIN" ) break;
			case NS_ERROR:       MFST_TRACE4 ( "------>NS_ERROR" ) break;
			case SURPRISE:       MFST_TRACE4 ( "------>SURPRISE" ) break;
			default: break;
		};
		return rc;
	};

	// ---------------- вспомогательные функции для печати ----------------

	char* Mfst::getCSt ( char* buf )                       // содержимое стека, вершина - первая
	{
		MFSTSTSTACK tmp = st;
		short k = 0;
		while ( !tmp.empty ( ) ) {
			buf[k++] = GRB::Rule::Chain::alphabet_to_char ( tmp.top ( ) );
			tmp.pop ( );
		}
		buf[k] = 0x00;
		return buf;
	};

	char* Mfst::getCLenta ( char* buf, short pos, short n )
	{
		short i, k = (pos + n < lenta_size) ? pos + n : lenta_size;
		for ( i = pos; i < k; i++ ) buf[i - pos] = GRB::Rule::Chain::alphabet_to_char ( lenta[i] );
		buf[(i - pos) > 0 ? i - pos : 0] = 0x00;
		return buf;
	};

	char* Mfst::getDiagnosis ( short n, char* buf )
	{
		buf[0] = 0x00;
		int errid = 0;
		int lpos = -1;
		if ( n < MFST_DIAGN_NUMBER && (lpos = diagnosis[n].lenta_position) >= 0 ) {
			errid = grebach.getRule ( diagnosis[n].nrule ).iderror;
			Error::ERROR err = Error::geterror ( errid );
			int idx = (lpos < lex.lextable.size) ? lpos : lex.lextable.size - 1;
			int line = (idx >= 0) ? lex.lextable.table[idx].sn : 0;
			snprintf ( buf, MFST_DIAGN_MAXSIZE, "%d: строка %d,  %s", err.id, line, err.message );
		};
		return buf;
	};
};