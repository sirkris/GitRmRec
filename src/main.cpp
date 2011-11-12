#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
	FILE *f;
	
#ifdef __linux__
	f = popen( "ls", "r" );
#elif defined __APPLE__
	f = popen( "ls", "r" );
#elif defined _WIN32 || defined __WIN64
	f = _popen( "dir", "r" );
#else
#error "Unknown platform!"
#endif

	if ( f == 0 )
	{
		fprintf( stderr, "Unable to execute!\r\n" );
		return 1;
	}

	const int BUFSIZE = 32767;
	char buf[BUFSIZE];

	while ( fgets( buf, sizeof( buf ), f ) )
	{
		fprintf( stdout, "%s", buf );
	}
	
	return 0;
}
