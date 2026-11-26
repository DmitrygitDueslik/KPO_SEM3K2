#include "stdafx.h"
namespace LT {
	LexTable Create(int size) {
		LexTable lt;
		lt.maxsize = size;
		lt.size = 0;
		lt.table = new Entry[size];
		return lt;
	}

	void Add(LexTable& lextable, Entry entry) {
		if (lextable.size < lextable.maxsize) {
			lextable.table[lextable.size] = entry;
			lextable.size++;
		}
	}
	Entry GetEntry(LexTable& lextable, int n) {
		return lextable.table[n];
	}
	void Delete(LexTable& lextable) {
		delete[] lextable.table;
		lextable.table = nullptr;
		lextable.size = 0;
		lextable.maxsize = 0;
	}
}