#include "stdafx.h"

namespace Error
{
	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY ( 0, "Íåäîïóñòèìûé êîä îøèáêè" ),
		ERROR_ENTRY ( 1, "Ñèñòåìíûé ñáîé" ),
		ERROR_ENTRY_NODEF ( 2 ), ERROR_ENTRY_NODEF ( 3 ), ERROR_ENTRY_NODEF ( 4 ),
		ERROR_ENTRY_NODEF ( 5 ), ERROR_ENTRY_NODEF ( 6 ), ERROR_ENTRY_NODEF ( 7 ),
		ERROR_ENTRY_NODEF ( 8 ), ERROR_ENTRY_NODEF ( 9 ),
		ERROR_ENTRY_NODEF10 ( 10 ), ERROR_ENTRY_NODEF10 ( 20 ),
		ERROR_ENTRY_NODEF10 ( 30 ), ERROR_ENTRY_NODEF10 ( 40 ),
		ERROR_ENTRY_NODEF10 ( 50 ), ERROR_ENTRY_NODEF10 ( 60 ),
		ERROR_ENTRY_NODEF10 ( 70 ), ERROR_ENTRY_NODEF10 ( 80 ),
		ERROR_ENTRY_NODEF10 ( 90 ),
		ERROR_ENTRY ( 100, "Ïàğàìåòğ -in äîëæåí áûòü çàäàí" ),
		ERROR_ENTRY ( 101, "Ïàğàìåòğ -in íå äîëæåí áûòü çàäàí" ),
		ERROR_ENTRY_NODEF ( 102 ), ERROR_ENTRY_NODEF ( 103 ),
		ERROR_ENTRY ( 104, "Ïğåâûøåíà äëèíà âõîäíîãî ïàğàìåòğà" ),
		ERROR_ENTRY_NODEF ( 105 ), ERROR_ENTRY_NODEF ( 106 ),
		ERROR_ENTRY_NODEF ( 107 ), ERROR_ENTRY_NODEF ( 108 ),
		ERROR_ENTRY_NODEF ( 109 ),
		ERROR_ENTRY ( 110, "Îøèáêà ïğè îòêğûòèè ôàéëà ñ èñõîäíûì êîäîì (-in)" ),
		ERROR_ENTRY ( 111, "Íåäîïóñòèìûé ñèìâîë â èñõîäíîì ôàéëå (-in)" ),
		ERROR_ENTRY ( 112, "Îøèáêà ïğè ñîçäàíèè ôàéëà ïğîòîêîëà (-log)" ),
		ERROR_ENTRY_NODEF ( 113 ), ERROR_ENTRY_NODEF ( 114 ),
		ERROR_ENTRY_NODEF ( 115 ), ERROR_ENTRY_NODEF ( 116 ),
		ERROR_ENTRY_NODEF ( 117 ), ERROR_ENTRY_NODEF ( 118 ),
		ERROR_ENTRY_NODEF ( 119 ),
		ERROR_ENTRY ( 120, "Èäåíòèôèêàòîğ ïğåâûøàåò ìàêñèìàëüíóş äëèíó (5 ñèìâîëîâ)" ),
		ERROR_ENTRY ( 121, "Íå çàêğûò ñòğîêîâûé ëèòåğàë (îòñóòñòâóåò çàâåğøàşùèé àïîñòğîô)" ),
		ERROR_ENTRY ( 122, "Ñòğîêîâûé ëèòåğàë ïğåâûøàåò ìàêñèìàëüíî äîïóñòèìóş äëèíó" ),
		ERROR_ENTRY ( 123, "Öåëî÷èñëåííûé ëèòåğàë âíå äîïóñòèìîãî äèàïàçîíà" ),
		ERROR_ENTRY ( 124, "Íåäîïóñòèìûé ñèìâîë ïğè ëåêñè÷åñêîì àíàëèçå" ),
		ERROR_ENTRY ( 125, "Ïåğåïîëíåíèå òàáëèöû ëåêñåì" ),
		ERROR_ENTRY ( 126, "Ïåğåïîëíåíèå òàáëèöû èäåíòèôèêàòîğîâ" ),
		ERROR_ENTRY_NODEF ( 127 ), ERROR_ENTRY_NODEF ( 128 ), ERROR_ENTRY_NODEF ( 129 ),
		ERROR_ENTRY_NODEF10 ( 130 ),
		ERROR_ENTRY_NODEF10 ( 140 ), ERROR_ENTRY_NODEF10 ( 150 ),
		ERROR_ENTRY_NODEF10 ( 160 ), ERROR_ENTRY_NODEF10 ( 170 ),
		ERROR_ENTRY_NODEF10 ( 180 ), ERROR_ENTRY_NODEF10 ( 190 ),
		ERROR_ENTRY_NODEF100 ( 200 ), ERROR_ENTRY_NODEF100 ( 300 ),
		ERROR_ENTRY_NODEF100 ( 400 ), ERROR_ENTRY_NODEF100 ( 500 ),
		ERROR_ENTRY ( 600, "Íåâåğíàÿ ñòğóêòóğà ïğîãğàììû" ),
		ERROR_ENTRY ( 601, "Îøèáî÷íûé îïåğàòîğ" ),
		ERROR_ENTRY ( 602, "Îøèáêà â âûğàæåíèè" ),
		ERROR_ENTRY ( 603, "Îøèáêà â ïàğàìåòğàõ ôóíêöèè" ),
		ERROR_ENTRY ( 604, "Îøèáêà â ïàğàìåòğàõ âûçûâàåìîé ôóíêöèè" ),
		ERROR_ENTRY_NODEF ( 605 ), ERROR_ENTRY_NODEF ( 606 ), ERROR_ENTRY_NODEF ( 607 ),
		ERROR_ENTRY_NODEF ( 608 ), ERROR_ENTRY_NODEF ( 609 ),
		ERROR_ENTRY_NODEF10 ( 610 ), ERROR_ENTRY_NODEF10 ( 620 ), ERROR_ENTRY_NODEF10 ( 630 ),
		ERROR_ENTRY_NODEF10 ( 640 ), ERROR_ENTRY_NODEF10 ( 650 ), ERROR_ENTRY_NODEF10 ( 660 ),
		ERROR_ENTRY_NODEF10 ( 670 ), ERROR_ENTRY_NODEF10 ( 680 ), ERROR_ENTRY_NODEF10 ( 690 ),
		ERROR_ENTRY_NODEF100 ( 700 ),
		ERROR_ENTRY_NODEF100 ( 800 ), ERROR_ENTRY_NODEF100 ( 900 )
	};

	ERROR geterror ( int id )
	{
		ERROR err;
		if ( id > 0 && id < ERROR_MAX_ENTRY ) {
			err = errors[id];
		}
		else {
			err = errors[0];
		}
		return err;
	}

	ERROR geterrorin ( int id, int line, int col )
	{
		ERROR err = geterror ( id );
		err.inext.line = (short)line;
		err.inext.col = (short)col;
		return err;
	}
}