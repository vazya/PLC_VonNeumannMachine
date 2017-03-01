#include "Interpreter.h"

void CInterpreter::readProgramm( const string & path )
{
	vector<string> programm;
	string s;
	fstream file( path );
	cout << path << endl;
	if( file.is_open() ) {
		cout << "VZ its open" << endl;
	}
	while( getline( file, s ) ) {
		programm.push_back( s );
		cout << s << endl;
	}
	file.close();
}

void CInterpreter::writeProgramm( const string & path )
{
}
