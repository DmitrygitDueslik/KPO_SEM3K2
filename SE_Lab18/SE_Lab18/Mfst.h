#pragma once
#include <stack>
#include <iostream>
#include <iomanip>
#include "GRB.h"
#include "LEX.h"

#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE   // размер строки диагностики
#define MFST_DIAGN_NUMBER  3                         // количество сохраняемых диагностик

typedef std::stack<short> MFSTSTSTACK;               // стек автомата

// заголовок трассировки
#define MFST_TRACE_START std::cout << std::setw(4)  << std::left << "Шаг" << ":"          \
                                   << std::setw(20) << std::left << " Правило"            \
                                   << std::setw(30) << std::left << " Входная лента"      \
                                   << std::setw(20) << std::left << " Стек"               \
                                   << std::endl;

namespace MFST
{
	struct MfstState                        // состояние автомата (для сохранения)
	{
		short lenta_position;               // позиция на ленте
		short nrulechain;                   // номер текущей цепочки, текущего правила
		MFSTSTSTACK st;                     // стек автомата
		MfstState ( );
		MfstState (
			short pposition,                // позиция на ленте
			MFSTSTSTACK pst,                // стек автомата
			short pnrulechain               // номер текущей цепочки, текущего правила
		);
	};

	struct Mfst                             // магазинный автомат
	{
		enum RC_STEP
		{                      // код возврата функции step
			NS_OK,                          // найдено правило и цепочка, цепочка записана в стек
			NS_NORULE,                      // не найдено правило грамматики (ошибка в грамматике)
			NS_NORULECHAIN,                 // не найдена подходящая цепочка правила (ошибка в исходном коде)
			NS_ERROR,                       // неизвестный нетерминальный символ грамматики
			TS_OK,                          // тек. символ ленты == вершине стека, продвинулась лента, pop стека
			TS_NOK,                         // тек. символ ленты != вершине стека, восстановлено состояние
			LENTA_END,                      // текущая позиция ленты >= lenta_size
			SURPRISE                        // неожиданный код возврата (ошибка в step)
		};

		struct MfstDiagnosis                // диагностика
		{
			short   lenta_position;         // позиция на ленте
			RC_STEP rc_step;                // код завершения шага
			short   nrule;                  // номер правила
			short   nrule_chain;            // номер цепочки правила
			MfstDiagnosis ( );
			MfstDiagnosis (
				short plenta_position,      // позиция на ленте
				RC_STEP prc_step,           // код завершения шага
				short pnrule,               // номер правила
				short pnrule_chain          // номер цепочки правила
			);
		} diagnosis[MFST_DIAGN_NUMBER];     // последние самые глубокие сообщения

		GRBALPHABET* lenta;                 // перекодированная (TS/NS) лента (из LEX)
		short lenta_position;               // текущая позиция на ленте
		short nrule;                        // номер текущего правила
		short nrulechain;                   // номер текущей цепочки, текущего правила
		short lenta_size;                   // размер ленты
		GRB::Greibach grebach;              // грамматика Грейбах
		LEX::LEX lex;                       // результат работы лексического анализатора
		MFSTSTSTACK st;                     // стек автомата
		std::stack<MfstState> storestate;   // стек для сохранения состояний
		Mfst ( );
		Mfst (
			LEX::LEX plex,                  // результат работы лексического анализатора
			GRB::Greibach pgrebach          // грамматика Грейбах
		);
		char* getCSt ( char* buf );            // получить содержимое стека
		char* getCLenta ( char* buf, short pos, short n = 25 );    // лента: n символов с pos
		char* getDiagnosis ( short n, char* buf );                 // получить n-ую строку диагностики или 0x00
		bool savestate ( );                   // сохранить состояние автомата
		bool reststate ( );                   // восстановить состояние автомата
		bool push_chain (                    // поместить цепочку правила в стек
			GRB::Rule::Chain chain          // цепочка правила
		);
		RC_STEP step ( );                     // выполнить шаг автомата
		bool start ( );                       // запустить автомат
		bool savediagnosis (
			RC_STEP pprc_step               // код завершения шага
		);
	};
};