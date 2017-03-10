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

void CInterpreter::writeByteCode( const string & path )
{
	//ofstream fout( path, ios::binary | ios::out );
	//fout.write( (char*)&code, sizeof code );
	//fout.close();
	ofstream fout( path, ios::binary | ios::out );
	for( int i = 0; i < code.size(); i++ ) {
		unsigned int cmd = code[i].getCMD();
		unsigned int dst = code[i].getDST();
		unsigned int src = code[i].getSRC();
		fout.write( (char*)&cmd, sizeof cmd );
		fout.write( (char*)&dst, sizeof dst );
		fout.write( (char*)&src, sizeof src );
	}
	fout.close();
}

void CInterpreter::readByteCode( const string & path )
{
	cout.width( 2 );
	ifstream fin( path, ios::binary | ios::in );
	unsigned int cmd, dst, src, i(0);
	do {
		fin.read( (char*)&cmd, sizeof cmd );
		fin.read( (char*)&dst, sizeof dst );
		fin.read( (char*)&src, sizeof src );
		cout << i << " : " << cmd << " " << dst << " " << src << endl;
		i++;
	} while( cmd != unsigned int( 15 ) );
	fin.close();
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
	//cout << "VZ programm.size = " << programm.size() << endl;
	//cout << "VZ code.size = " << code.size() << endl;
	//printProgramm();
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
		if( cmd == string( "cmp" ) || cmd == string( "CMP" ) ) {
			createCMPRegs( tokens );
		}
		if( cmd == string( "jmp" ) || cmd == string( "JMP" ) ) {
			createJMPRegs( tokens );
		}
		if( cmd == string( "shu" ) || cmd == string( "SHU" ) ) {
			createSHURegs( tokens );
		}
		if( cmd == string( "shd" ) || cmd == string( "SHD" ) ) {
			createSHDRegs( tokens );
		}
		if( cmd == string( "outc" ) || cmd == string( "OUTC" ) ) {
			createOUTCRegs( tokens );
		}
		//if( cmd == string( "je" ) || cmd == string( "JE" ) ) {
		//	createJERegs( tokens );
		//}
		//if( cmd == string( "jne" ) || cmd == string( "JNE" ) ) {
		//	createJNERegs( tokens );
		//}
		if( cmd == string( "stop" ) || cmd == string( "STOP" ) ) {
			createSTOPRegs( tokens );
			return;
		}
		if( cmd == string( "var" ) || cmd == string( "VAR" ) ) {
			createVARRegs( tokens );
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
	unsigned int dst = getVar( tokens[1] ); // std::stoi( tokens[1] );
	unsigned int src = getVar( tokens[2] ); // std::stoi( tokens[2] );
	code.push_back( CRegs( 2, dst, src ) );
}

void CInterpreter::createSETRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 3 );
	unsigned int dst = getVar( tokens[1] ); // std::stoi( tokens[1] );
	unsigned int src = getVar( tokens[2] ); // std::stoi( tokens[2] );
	code.push_back( CRegs( 3, dst, src ) );
}

void CInterpreter::createINRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int src = getVar( tokens[1] ); // std::stoi( tokens[1] );
	code.push_back( CRegs( 4, 0, src ) );
}

void CInterpreter::createOUTRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int src = getVar	( tokens[1] ); // std::stoi( tokens[1] );
	code.push_back( CRegs( 5, 0, src ) );
}

void CInterpreter::createINCRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int dst = getVar( tokens[1] ); // std::stoi( tokens[1] );
	code.push_back( CRegs( 6, 0, dst ) );
}

void CInterpreter::createDECRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int dst = getVar( tokens[1] ); // std::stoi( tokens[1] );
	code.push_back( CRegs( 7, 0, dst ) );
}

void CInterpreter::createADDRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 3 );
	unsigned int dst = getVar( tokens[1] ); // std::stoi( tokens[1] );
	unsigned int src = getVar( tokens[2] ); // std::stoi( tokens[2] );
	code.push_back( CRegs( 8, dst, src ) );
}

void CInterpreter::createSUBRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 3 );
	unsigned int dst = getVar( tokens[1] ); // std::stoi( tokens[1] );
	unsigned int src = getVar( tokens[2] ); // std::stoi( tokens[2] );
	code.push_back( CRegs( 9, dst, src ) );
}

void CInterpreter::createCMPRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 3 );
	unsigned int dst = getVar( tokens[1] ); // std::stoi( tokens[1] );
	unsigned int src = getVar( tokens[2] ); // std::stoi( tokens[2] );
	code.push_back( CRegs( 10, dst, src ) );
}

void CInterpreter::createJMPRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int src = std::stoi( tokens[1] );
	code.push_back( CRegs( 11, 0, src ) );
}

void CInterpreter::createSHURegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int src = std::stoi( tokens[1] );
	code.push_back( CRegs( 12, 0, src ) );
}

void CInterpreter::createSHDRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int src = std::stoi( tokens[1] );
	code.push_back( CRegs( 13, 0, src ) );
}

void CInterpreter::createOUTCRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int src = std::stoi( tokens[1] );
	code.push_back( CRegs( 14, 0, src ) );
}


//void CInterpreter::createJERegs( const vector<string>& tokens )
//{
//	assert( tokens.size() == 2 );
//	unsigned int src = std::stoi( tokens[1] );
//	code.push_back( CRegs( 12, 0, src ) );
//}
//
//void CInterpreter::createJNERegs( const vector<string>& tokens )
//{
//	assert( tokens.size() == 2 );
//	unsigned int src = std::stoi( tokens[1] );
//	code.push_back( CRegs( 13, 0, src ) );
//}

void CInterpreter::createSTOPRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 1 );
	code.push_back( CRegs( 15, 0, 0 ) );
}

bool CInterpreter::checkVar( const string & name )
{
	if( vars.find( name ) != vars.end() ) {
		return true;
	}
	return false;
}

unsigned int CInterpreter::getVar( const string & name )
{
	if( checkVar( name ) ) {
		return vars[name];
	}
	return unsigned int( std::stoi( name ) );
}

void CInterpreter::createVARRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 3 );

	string varName = tokens[1];
	unsigned int src = std::stoi( tokens[2] );
	vars.insert( pair<string, unsigned int>( varName, src ) );

	code.push_back( CRegs( 16, 0, src ) );
}
