#include "FST.h"
#include <cstdarg>
#include <cstring>
namespace FST {
	RELATION::RELATION(char c, short ns) {
		symbol = c;
		nnode = ns;
	}
	NODE::NODE() {
		n_relation = 0;
		relations = nullptr;
	}
	NODE::NODE(short n, RELATION rel, ...) {
		n_relation = n;
		relations = new RELATION[n_relation];
		va_list args;
		va_start(args, rel);
		relations[0] = rel;
		for (short i = 1; i < n_relation; i++) {
			relations[i] = va_arg(args, RELATION);
		}
		va_end(args);
	}
	FST::FST(char* s, short ns, NODE n, ...) {
		string = s;
		position = 0;
		nstates = ns;
		nodes = new NODE[nstates];
		va_list args;
		va_start(args, n);
		nodes[0] = n;
		for (short i = 1; i < nstates; i++) {
			nodes[i] = va_arg(args, NODE);
		}
		va_end(args);
		rstates = new short[nstates];
		memset(rstates, 0, sizeof(short) * nstates);
	}
	bool execute(FST& fst) {
		int n = fst.nstates;
		int len = (int)strlen(fst.string);
		short* cur = new short[n];
		short* nxt = new short[n];

		cur[0] = 0;
		for (int i = 1;i < n;i++)
		{
			cur[i] = -1;
		}
		fst.position = 0;
		while (fst.position < len) {
			char ch =fst.string[fst.position];
			for (int i = 0;i < n;i++)
			{
				nxt[i] = -1;
			}
			bool anyActive = false;
			for (int s = 0;s < n;s++) {
				if (cur[s] == -1) {
					continue;
				}
				NODE& node = fst.nodes[s];
				for (int r = 0;r < node.n_relation;r++) {
					if (node.relations[r].symbol == ch) {
						short target = node.relations[r].nnode;
						nxt[target] = cur[s] + 1;
						anyActive = true;

					}
				}
			}
			short* tmp = cur;
			cur = nxt;
			nxt = tmp;
			fst.position++;

			if (!anyActive)
			{
				break;
			}

		}
		fst.rstates = cur;
		delete[] nxt;
		return fst.rstates[n - 1] == len;
	}
}