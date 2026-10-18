#include <iostream>
#include <clocale>
#include <fstream>
#include <string>
using namespace std;

int main ( )
{
	setlocale ( LC_ALL, "rus" );

	ifstream in ( "..\\data.bin", ios::binary );
	if ( !in ) {
		cout << "Файл data.bin не найден" << endl;
		return 1;
	}

	ofstream out ( "..\\Asm4\\asm04.asm" );
	if ( !out ) {
		cout << "Не удалось создать asm04.asm " << endl;
		return 1;
	}
	out << ".586P\n";
	out << ".MODEL FLAT, STDCALL\n";
	out << "includelib kernel32.lib\n";
	out << "ExitProcess PROTO :DWORD\n";
	out << ".STACK 4096\n";
	out << ".DATA\n";

	string code;
	char type;
	int n = 0;

	while ( in.read ( &type, 1 ) ) {
		if ( type == 0x01 ) {                          // short
			short v;
			in.read ( (char*)&v, 2 );
			cout << "0x01 short          " << v << endl;

			//  Генерация кода
			out << "T" << n << "\tBYTE\t01h\n";
			out << "V" << n << "\tSWORD\t" << v << "\n";
			code += "\tmovsx\teax, V" + to_string ( n ) + "\n";
		}
		else if ( type == 0x02 ) {                     // unsigned short
			unsigned short v;
			in.read ( (char*)&v, 2 );
			cout << "0x02 unsigned short " << v << endl;

			out << "T" << n << "\tBYTE\t02h\n";
			out << "V" << n << "\tWORD\t" << v << "\n";
			code += "\tmovzx\teax, V" + to_string ( n ) + "\n";
		}
		else {
			cout << "Ошибка: неизвестный тип " << (int)type << endl;
			return 1;
		}
		n++;
	}

	out << ".CODE\n";
	out << "main PROC\n";
	out << code;
	out << "\tpush\t0\n";
	out << "\tcall\tExitProcess\n";
	out << "main ENDP\n";
	out << "end main\n";
	out.close ( );

	cout << "Создан файл asm04.asm" << endl;
	return 0;
}