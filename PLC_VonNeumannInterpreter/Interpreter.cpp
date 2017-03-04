#include "Interpreter.h"

void CInterpreter::printProgramm()
{
	for( int i = 0; i < code.size(); i++ ) {
		cout.width( 2 );
		cout << i << " : ";
		code[i].print();
	}
}

void CInterpreter::writeProgramm( const string & path )
{
	// пока что закостылим на обычный файл
	ofstream fout(path);
	for( int i = 0; i < code.size(); i++ ) {
		code[i].fprint( fout );
	}
	fout.close();
}

void CInterpreter::readProgramm( const string & path )
{
	vector<string> programm;
	string line;
	fstream file( path );

	while( getline( file, line ) ) {
		if( !line.empty() ) {
			programm.push_back( line );
			parseCommand( line );
		}
	}
	file.close();
	cout << "VZ programm.size = " << programm.size() << endl;
	cout << "VZ code.size = " << code.size() << endl;
	printProgramm();
}

void CInterpreter::parseCommand( const string & line )
{
	// пилим строку на токены
	vector<string> tokens;
	int counter = 0;
	while( counter < line.length() ) {
		string token;
		char c = line[counter];
		while( c != '\0' && c != ' ' && c != '\n' && c != '\r' && c != ',' && c != ':' ) {
			if( c != ',' && c != ':' ) {
				token.push_back( c );
			}
			counter++;
			c = line[counter];
		}
		if( !token.empty() ) {
			tokens.push_back( token );
			token.clear();
		}
		counter++;
	}
	createRegs( tokens );
}

void CInterpreter::createRegs( const vector<string>& tokens )
{
	if( tokens.empty() ) {
		assert( false );
	} else {
		string cmd = tokens[0];
		if( cmd == string( "ip" ) || cmd == string( "IP" ) ) {
			createIPRegs( tokens );
		}
		if( cmd == string( "mov" ) || cmd == string( "MOV" ) ) {
			createMOVRegs( tokens );
		}
		if( cmd == string( "set" ) || cmd == string( "SET" ) ) {
			createSETRegs( tokens );
		}
		if( cmd == string( "in" ) || cmd == string( "IN" ) ) {
			createINRegs( tokens );
		}
		if( cmd == string( "out" ) || cmd == string( "OUT" ) ) {
			createOUTRegs( tokens );
		}
		if( cmd == string( "inc" ) || cmd == string( "INC" ) ) {
			createINCRegs( tokens );
		}
		if( cmd == string( "dec" ) || cmd == string( "DEC" ) ) {
			createDECRegs( tokens );
		}
		if( cmd == string( "add" ) || cmd == string( "ADD" ) ) {
			createADDRegs( tokens );
		}
		if( cmd == string( "sub" ) || cmd == string( "SUB" ) ) {
			createSUBRegs( tokens );
		}
		if( cmd == string( "jmp" ) || cmd == string( "JMP" ) ) {
			createJMPRegs( tokens );
		}
		if( cmd == string( "call" ) || cmd == string( "CALL" ) ) {
			createCALLRegs( tokens );
		}
		if( cmd == string( "ret" ) || cmd == string( "RET" ) ) {
			createRETRegs( tokens );
		}
		if( cmd == string( "label" ) || cmd == string( "LABEL" ) ) {
			createLABELRegs( tokens );
		}
		if( cmd == string( "stop" ) || cmd == string( "STOP" ) ) {
			createSTOPRegs( tokens );
			return;
		}

	}
	//cout << "VZ undefined command = " << tokens[0] << endl;
}

void CInterpreter::createIPRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int p = std::stoi( tokens[1] );
	if( p > 255 ) {
		p = 255;
	}
	code.push_back( CRegs( 1, 0, p ) );
	for( int i = 0; i < p; i++ ) {
		code.push_back( CRegs() );
	}
}

void CInterpreter::createMOVRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 3 );
	unsigned int dst = std::stoi( tokens[1] );
	unsigned int src = std::stoi( tokens[2] );
	code.push_back( CRegs( 2, dst, src ) );
}

void CInterpreter::createSETRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 3 );
	unsigned int dst = std::stoi( tokens[1] );
	unsigned int src = std::stoi( tokens[2] );
	code.push_back( CRegs( 3, dst, src ) );
}

void CInterpreter::createINRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int src = std::stoi( tokens[1] );
	code.push_back( CRegs( 4, 0, src ) );
}

void CInterpreter::createOUTRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int src = std::stoi( tokens[1] );
	code.push_back( CRegs( 5, 0, src ) );
}

void CInterpreter::createINCRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int dst = std::stoi( tokens[1] );
	code.push_back( CRegs( 6, 0, dst ) );
}

void CInterpreter::createDECRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int dst = std::stoi( tokens[1] );
	code.push_back( CRegs( 7, 0, dst ) );
}

void CInterpreter::createADDRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 3 );
	unsigned int dst = std::stoi( tokens[1] );
	unsigned int src = std::stoi( tokens[2] );
	code.push_back( CRegs( 8, dst, src ) );
}

void CInterpreter::createSUBRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 3 );
	unsigned int dst = std::stoi( tokens[1] );
	unsigned int src = std::stoi( tokens[2] );
	code.push_back( CRegs( 9, dst, src ) );
}

void CInterpreter::createJMPRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int src = std::stoi( tokens[1] );
	code.push_back( CRegs( 11, 0, src ) );
}




void CInterpreter::createCALLRegs( const vector<string>& tokens )
{
	assert( false );
}

void CInterpreter::createRETRegs( const vector<string>& tokens )
{
	assert( false );
}

void CInterpreter::createLABELRegs( const vector<string>& tokens )
{
	assert( false );
}

void CInterpreter::createSTOPRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 1 );
	code.push_back( CRegs( 15, 0, 0 ) );
}

