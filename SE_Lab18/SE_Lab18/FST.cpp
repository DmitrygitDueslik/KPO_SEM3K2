#include "stdafx.h"
namespace FST
{
	RELATION::RELATION ( char c, short ns )
	{
		symbol = c;
		nnode = (char)ns;
	}
	NODE::NODE ( )
	{
		n_relation = 0;
		relations = nullptr;
	}
	NODE::NODE ( short n, RELATION rel, ... )
	{
		n_relation = n;
		relations = new RELATION[n_relation];
		va_list args;
		va_start ( args, rel );
		relations[0] = rel;
		for ( short i = 1; i < n_relation; i++ ) {
			relations[i] = va_arg ( args, RELATION );
		}
		va_end ( args );
	}
	FST::FST ( char* s, short ns, NODE n, ... )
	{
		string = s;
		position = -1;
		nstates = ns;
		nodes = new NODE[nstates];
		va_list args;
		va_start ( args, n );
		nodes[0] = n;
		for ( short i = 1; i < nstates; i++ ) {
			nodes[i] = va_arg ( args, NODE );
		}
		va_end ( args );
		rstates = new short[nstates];
		memset ( rstates, 0xff, sizeof ( short ) * nstates );
		rstates[0] = 0;
	}

	static bool step ( FST& fst, short* cur, short* nxt )
	{
		bool rc = false;
		for ( short i = 0; i < fst.nstates; i++ ) {
			if ( cur[i] != fst.position ) continue;
			for ( short j = 0; j < fst.nodes[i].n_relation; j++ ) {
				if ( fst.nodes[i].relations[j].symbol == fst.string[fst.position] ) {
					nxt[fst.nodes[i].relations[j].nnode] = fst.position + 1;
					rc = true;
				}
			}
		}
		return rc;
	}

	bool execute ( FST& fst )
	{
		short n = fst.nstates;
		short len = (short)strlen ( fst.string );

		short* cur = new short[n];
		short* nxt = new short[n];
		memset ( cur, 0xff, sizeof ( short ) * n );
		memset ( nxt, 0xff, sizeof ( short ) * n );
		cur[0] = 0;

		bool rc = true;
		fst.position = -1;
		for ( short i = 0; i < len && rc; i++ ) {
			fst.position++;
			rc = step ( fst, cur, nxt );
			short* tmp = cur;
			cur = nxt;
			nxt = tmp;
		}

		bool ok = rc && (cur[n - 1] == len);
		memcpy ( fst.rstates, cur, sizeof ( short ) * n );

		delete[] cur;
		delete[] nxt;
		return ok;
	}
}