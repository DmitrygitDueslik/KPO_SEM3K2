#include "stdafx.h"


namespace IT{
	IdTable Create(int size) {
		IdTable it;
		it.maxsize = size;
		it.size = 0;
		it.table = new Entry[size];
		return it;
	}

	void Add(IdTable& idtable, Entry entry) {
		if (idtable.size < idtable.maxsize) {
			idtable.table[idtable.size] = entry;
			idtable.size++;
		}
	}
	Entry GetEntry(IdTable& idtable, int n) {
		return idtable.table[n];
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE]) {
		for (int i = 0;i < idtable.size;i++) {
			if (strncmp(idtable.table[i].id, id, ID_MAXSIZE) == 0) {
				return i;
			}
		}
		return TI_NULLIDX;
	}
	void Delete(IdTable& idtable) {
		delete[]idtable.table;
		idtable.table = nullptr;
		idtable.size = 0;
		idtable.maxsize = 0;
	}
}