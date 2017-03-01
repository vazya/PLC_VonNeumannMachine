#include "Interpreter.h"

void CInterpreter::writeProgramm( const string & path )
{
}

void CInterpreter::readProgramm( const string & path )
{
	vector<string> programm;
	string line;
	fstream file( path );

	while( getline( file, line ) ) {
		if( !line.empty() ) {
			programm.push_back( line );
			cout << line << endl;
			parseCommand( line );
		}
	}
	file.close();
	cout << "VZ programm.size = " << programm.size() << endl;
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
	code.push_back( createRegs( tokens ) );
}

const CRegs& CInterpreter::createRegs( const vector<string>& tokens )
{
	if( tokens.empty() ) {
		assert( false );
	} else {
		if( tokens[0] == string( "ip" ) || tokens[0] == string( "IP" ) ) {
			return createIPRegs( tokens );
		}
		if( tokens[0] == string( "mov" ) || tokens[0] == string( "MOV" ) ) {
			return createMOVRegs( tokens );
		}
		if( tokens[0] == string( "in" ) || tokens[0] == string( "IN" ) ) {
			return createINRegs( tokens );
		}
		if( tokens[0] == string( "out" ) || tokens[0] == string( "OUT" ) ) {
			return createOUTRegs( tokens );
		}
		if( tokens[0] == string( "inc" ) || tokens[0] == string( "INC" ) ) {
			return createINCRegs( tokens );
		}
		if( tokens[0] == string( "dec" ) || tokens[0] == string( "DEC" ) ) {
			return createDECRegs( tokens );
		}
		if( tokens[0] == string( "jmp" ) || tokens[0] == string( "JMP" ) ) {
			return createJMPRegs( tokens );
		}
		if( tokens[0] == string( "call" ) || tokens[0] == string( "CALL" ) ) {
			return createCALLRegs( tokens );
		}
		if( tokens[0] == string( "ret" ) || tokens[0] == string( "RET" ) ) {
			return createRETRegs( tokens );
		}
		if( tokens[0] == string( "label" ) || tokens[0] == string( "LABEL" ) ) {
			return createLABELRegs( tokens );
		}
		if( tokens[0] == string( "stop" ) || tokens[0] == string( "STOP" ) ) {
			return createSTOPRegs( tokens );
		}

	}
	cout << "VZ undefined command = " << tokens[0] << endl;
	return CRegs();
}

const CRegs& CInterpreter::createIPRegs( const vector<string>& tokens )
{
	//cout << "VZ IP" << endl;
	CRegs( 1, 0, 0, 0 );
	return CRegs();
}

const CRegs& CInterpreter::createMOVRegs( const vector<string>& tokens )
{
	//cout << "VZ mov" << endl;
	CRegs( 2, 0, 0, 0 );
	return CRegs();
}

const CRegs& CInterpreter::createINRegs( const vector<string>& tokens )
{
	//cout << "VZ in" << endl;
	CRegs( 3, 0, 0, 0 );
	return CRegs();
}

const CRegs& CInterpreter::createOUTRegs( const vector<string>& tokens )
{
	//cout << "VZ out" << endl;
	CRegs( 4, 0, 0, 0 );
	return CRegs();
}

const CRegs& CInterpreter::createINCRegs( const vector<string>& tokens )
{
	//cout << "VZ inc" << endl;
	CRegs( 5, 0, 0, 0 );
	return CRegs();
}


const CRegs& CInterpreter::createDECRegs( const vector<string>& tokens )
{
	//cout << "VZ dec" << endl;
	CRegs( 6, 0, 0, 0 );
	return CRegs();
}


const CRegs& CInterpreter::createJMPRegs( const vector<string>& tokens )
{
	//cout << "VZ jmp" << endl;
	CRegs( 7, 0, 0, 0 );
	return CRegs();
}


const CRegs& CInterpreter::createCALLRegs( const vector<string>& tokens )
{
	//cout << "VZ call" << endl;
	if( tokens.size() > 4 ) {
		cout << "VZ createCALLRegs get more than 1 token" << endl;
		assert( false );
	}
	CRegs( 8, 0, 0, 0 );
	return CRegs();
}


const CRegs& CInterpreter::createRETRegs( const vector<string>& tokens )
{
	//cout << "VZ ret" << endl;
	if( tokens.size() > 1 ) {
		cout << "VZ createRETRegs get more than 1 token" << endl;
		assert( false );
	}
	CRegs( 9, 0, 0, 0 );
	return CRegs();
}


const CRegs& CInterpreter::createLABELRegs( const vector<string>& tokens )
{
	//cout << "VZ label" << endl;
	if( tokens.size() > 1 ) {
		cout << "VZ createLABELRegs get more than 1 token" << endl;
		assert( false );
	}
	CRegs( 10, 0, 0, 0 );
	return CRegs();
}


const CRegs& CInterpreter::createSTOPRegs( const vector<string>& tokens )
{
	//cout << "VZ stop" << endl;
	if( tokens.size() > 1 ) {
		cout << "VZ createSTOPRegs get more than 1 token" << endl;
		assert( false );
	}
	CRegs( 15, 0, 0, 0 );
	return CRegs();
}

