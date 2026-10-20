#include <iostream>
#include <clocale>
#include <fstream>
#include <cstring>
using namespace std;

int main ( )
{
	setlocale ( LC_ALL, "rus" );

	short  a[4] = { 11, -22,-44,55 };  // переменные
	unsigned short b[3] = { 76,245,31000 };           // литералы (2 байта)

	unsigned char plan[100];
	int size = 0;

	for ( int i = 0; i < 4; i++ ) {
		plan[size] = 0x01;
		size++;
		memcpy ( &plan[size], &a[i], 2 );
		size += 2;
		cout << "0x01 short          " << a[i] << endl;
	}

	for ( int i = 0; i < 3; i++ ) {
		plan[size] = 0x02;
		size++;
		memcpy ( &plan[size], &b[i], 2 );
		size += 2;
		cout << "0x02 unsigned short " << b[i] << endl;
	}

	ofstream file ( "..\\data.bin", ios::binary );
	file.write ( (char*)plan, size );
	file.close ( );

	cout << "«аписано байт: " << size << endl;
	return 0;
}