#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>

using namespace std;

int main()
{
	FILE *f;
	FILE *ff;
	
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
	char buf2[BUFSIZE];
	size_t pos;
	string s;
	string del = "deleted:";
	const char *gitc;

	/* Reads the output, one line at a time.  --Kris */
	while ( fgets( buf, sizeof( buf ), f ) )
	{
		//fprintf( stdout, "%s", buf );
		if ( strstr( buf, del.c_str() ) != NULL )
		{
			s = string( buf );

			pos = s.find( del ) + del.length();
			s = s.substr( pos );

			/* Trim leading tabs and/or whitespace.  --Kris */
			s = s.erase( 0, s.find_first_not_of( " \t" ) );
			s = s.erase( s.find_last_not_of( " \t\r\n" ) + 1 );

			/* Build the Git command.  --Kris */
			s = "git rm --cached " + s;

			/* Make usable by popen.  --Kris */
			gitc = s.c_str();

			/* Execute and we're done!  --Kris */
			cout << "Output of '" + s + "':  ";

			#ifdef __linux__
				ff = popen( gitc, "r" );
			#elif defined __APPLE__
				ff = popen( gitc, "r" );
			#elif defined _WIN32 || defined __WIN64
				ff = _popen( gitc, "r" );
			#else
			#error "Unknown platform!"
			#endif

			if ( ff == 0 )
			{
				fprintf( stderr, "Unable to execute!\r\n" );
				return 1;
			}

			while ( fgets( buf2, sizeof( buf2 ), ff ) )
			{
				fprintf( stdout, "%s", buf2 );
			}
		}
	}
	
	return 0;
}
