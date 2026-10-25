#include "stdafx.h"
#include "MFST.h"

// ---------------- отладочный вывод  ----------------
static int  FST_TRACE_n = -1;                   // номер шага
static char rbuf[205];                          // буфер для правила
static char sbuf[MFST_STR_MAXSIZE];             // буфер для стека
static char lbuf[MFST_STR_MAXSIZE];             // буфер для ленты

// шаг с правилом: номер, правило, лента, стек
#define MFST_TRACE1 std::cout << std::setw(4) << std::left << ++FST_TRACE_n << ": " \
	<< std::setw(20) << std::left << rule.getCRule(rbuf, nrulechain)                   \
	<< std::setw(30) << std::left << getCLenta(lbuf, lenta_position)                   \
	<< std::setw(20) << std::left << getCSt(sbuf) << std::endl;

// состояние после шага (номер шага не меняется)
#define MFST_TRACE2 std::cout << std::setw(4) << std::left << FST_TRACE_n << ": "   \
	<< std::setw(20) << std::left << " "                                               \
	<< std::setw(30) << std::left << getCLenta(lbuf, lenta_position)                   \
	<< std::setw(20) << std::left << getCSt(sbuf) << std::endl;

// новый шаг без правила (сдвиг ленты)
#define MFST_TRACE3 std::cout << std::setw(4) << std::left << ++FST_TRACE_n << ": " \
	<< std::setw(20) << std::left << " "                                               \
	<< std::setw(30) << std::left << getCLenta(lbuf, lenta_position)                   \
	<< std::setw(20) << std::left << getCSt(sbuf) << std::endl;

// новый шаг с сообщением
#define MFST_TRACE4(c) std::cout << std::setw(4) << std::left << ++FST_TRACE_n << ": " \
	<< std::setw(20) << std::left << c << std::endl;

// сообщение в текущем шаге
#define MFST_TRACE5(c) std::cout << std::setw(4) << std::left << FST_TRACE_n << ": "   \
	<< std::setw(20) << std::left << c << std::endl;

// сообщение с числом в текущем шаге
#define MFST_TRACE6(c, k) std::cout << std::setw(4) << std::left << FST_TRACE_n << ": " \
	<< std::setw(20) << std::left << c << k << std::endl;