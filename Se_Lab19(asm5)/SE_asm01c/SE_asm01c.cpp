#include <iostream>
using namespace std;

#pragma comment(lib, "..\\Debug\\SE_asm01a.lib")

extern "C" int __stdcall getmin ( int* arr, int count );
extern "C" int __stdcall getmax ( int* arr, int count );

int main ( )
{
	int massiv[10] = { 12, -5, 33, 7, -12, 18, 0, 95, -3, 9 };

	int mn = getmin ( massiv, 10 );
	int mx = getmax ( massiv, 10 );

	cout << "getmax + getmin = " << mx + mn << endl;
	return 0;
}