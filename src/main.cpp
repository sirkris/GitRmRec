#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>

using namespace std;

int main()
{
	FILE *f;
	
#ifdef __linux__
	f = popen( "git status", "r" );
#elif defined __APPLE__
	f = popen( "git status", "r" );
#elif defined _WIN32 || defined __WIN64
	f = _popen( "git status", "r" );
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
	size_t pos;
	string s;
	string del = "deleted:";

	/* Reads the output, one line at a time.  --Kris */
	while ( fgets( buf, sizeof( buf ), f ) )
	{
		//fprintf( stdout, "%s", buf );
		if ( strstr( buf, "deleted:" ) != NULL )
		{
			s = string( buf );

			pos = s.find( del ) + del.length();
			s = s.substr( pos );

			/* Trim leading tabs and/or whitespace.  --Kris */
			s = s.erase( 0, s.find_first_not_of( " \t" ) );

			cout << s;
		}
	}
	
	return 0;
}
