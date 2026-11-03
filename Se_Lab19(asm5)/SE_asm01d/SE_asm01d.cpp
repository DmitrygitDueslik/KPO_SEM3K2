extern "C" int getmin ( int* arr, int count )
{
	int m = arr[0];
	for ( int i = 1; i < count; i++ )
		if ( arr[i] < m )
			m = arr[i];
	return m;
}

extern "C" int getmax ( int* arr, int count )
{
	int m = arr[0];
	for ( int i = 1; i < count; i++ )
		if ( arr[i] > m )
			m = arr[i];
	return m;
}