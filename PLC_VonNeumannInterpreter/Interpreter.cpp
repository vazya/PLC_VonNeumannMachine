#include "Interpreter.h"

void CInterpreter::printProgramm()
{
	for( int i = 0; i < code.size(); i++ ) {
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
		if( tokens[0] == string( "ip" ) || tokens[0] == string( "IP" ) ) {
			createIPRegs( tokens );
		}
		if( tokens[0] == string( "mov" ) || tokens[0] == string( "MOV" ) ) {
			createMOVRegs( tokens );
		}
		if( tokens[0] == string( "set" ) || tokens[0] == string( "SET" ) ) {
			createSETRegs( tokens );
		}
		if( tokens[0] == string( "in" ) || tokens[0] == string( "IN" ) ) {
			createINRegs( tokens );
		}
		if( tokens[0] == string( "out" ) || tokens[0] == string( "OUT" ) ) {
			createOUTRegs( tokens );
		}
		if( tokens[0] == string( "inc" ) || tokens[0] == string( "INC" ) ) {
			createINCRegs( tokens );
		}
		if( tokens[0] == string( "dec" ) || tokens[0] == string( "DEC" ) ) {
			createDECRegs( tokens );
		}
		if( tokens[0] == string( "add" ) || tokens[0] == string( "ADD" ) ) {
			createADDRegs( tokens );
		}
		if( tokens[0] == string( "sub" ) || tokens[0] == string( "SUB" ) ) {
			createSUBRegs( tokens );
		}
		if( tokens[0] == string( "jmp" ) || tokens[0] == string( "JMP" ) ) {
			createJMPRegs( tokens );
		}
		if( tokens[0] == string( "call" ) || tokens[0] == string( "CALL" ) ) {
			createCALLRegs( tokens );
		}
		if( tokens[0] == string( "ret" ) || tokens[0] == string( "RET" ) ) {
			createRETRegs( tokens );
		}
		if( tokens[0] == string( "label" ) || tokens[0] == string( "LABEL" ) ) {
			createLABELRegs( tokens );
		}
		if( tokens[0] == string( "stop" ) || tokens[0] == string( "STOP" ) ) {
			createSTOPRegs( tokens );
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
	code.push_back( CRegs( 1, 0, 0, 0, p ) );
	for( int i = 0; i < p; i++ ) {
		code.push_back( CRegs() );
	}
}

void CInterpreter::createMOVRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 3 );
	unsigned int dst = std::stoi( tokens[1] );
	unsigned int src = std::stoi( tokens[2] );
	code.push_back( CRegs( 2, 0, dst, 0, src ) );
}

void CInterpreter::createSETRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 3 );
	unsigned int dst = std::stoi( tokens[1] );
	unsigned int src = std::stoi( tokens[2] );
	code.push_back( CRegs( 3, 0, dst, 0, src ) );
}

void CInterpreter::createINRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int dst = std::stoi( tokens[1] );
	code.push_back( CRegs( 4, 0, 0, 0, dst ) );
}

void CInterpreter::createOUTRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int src = std::stoi( tokens[1] );
	code.push_back( CRegs( 5, 0, 0, 0, src ) );
}

void CInterpreter::createINCRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int dst = std::stoi( tokens[1] );
	code.push_back( CRegs( 6, 0, 0, 0, dst ) );
}

void CInterpreter::createDECRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int dst = std::stoi( tokens[1] );
	code.push_back( CRegs( 7, 0, 0, 0, dst ) );
}

void CInterpreter::createADDRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 3 );
	unsigned int dst = std::stoi( tokens[1] );
	unsigned int src = std::stoi( tokens[2] );
	code.push_back( CRegs( 8, 0, dst, 0, src ) );
}

void CInterpreter::createSUBRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 3 );
	unsigned int dst = std::stoi( tokens[1] );
	unsigned int src = std::stoi( tokens[2] );
	code.push_back( CRegs( 9, 0, dst, 0, src ) );
}





void CInterpreter::createJMPRegs( const vector<string>& tokens )
{
	assert( false );
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
	code.push_back( CRegs( 15, 0, 0, 0, 0 ) );
}

