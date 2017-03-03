#include "VMachine.h"

void CVMachine::printProgramm()
{
	for( int i = 0; i < code.size(); i++ ) {
		code[i].print();
	}
}

void CVMachine::writeProgramm( const string & path )
{
	// пока что закостылим на обычный файл
	ofstream fout( path );
	for( int i = 0; i < code.size(); i++ ) {
		code[i].fprint( fout );
	}
	fout.close();
}

void CVMachine::readProgramm( const string & path )
{
	string line;
	fstream file( path );

	while( getline( file, line ) ) {
		if( !line.empty() ) {
			cout << line << endl;
			// process Command(line);
		}
	}
	file.close();
	cout << "VZ code.size = " << code.size() << endl;
	printProgramm();
}
