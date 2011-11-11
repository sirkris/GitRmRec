#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
	FILE *f = _popen( "ls", "r" );

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
