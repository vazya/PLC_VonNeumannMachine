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
		//cout << "VZ " << line << endl;
		if( !line.empty() ) {
			programm.push_back( line );
			parseCommand( line );
		}
	}
	file.close();
	restoreLabels();
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
		while( c != '\0' && c != ' ' && c != '\n' && c != '\r' && c != ',' && c != ':' && c != '	'  && c != '\t' ) {
			if( c != ',' && c != ':') {
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
		if( cmd[0] == '@' ) {
			createLABELRegs( tokens );
			return;
		}
		if( cmd == string( "ip" ) || cmd == string( "IP" ) ) {
			createIPRegs( tokens );
			return;
		}
		if( cmd == string( "mov" ) || cmd == string( "MOV" ) ) {
			createMOVRegs( tokens );
			return;
		}
		if( cmd == string( "set" ) || cmd == string( "SET" ) ) {
			createSETRegs( tokens );
			return;
		}
		if( cmd == string( "in" ) || cmd == string( "IN" ) ) {
			createINRegs( tokens );
			return;
		}
		if( cmd == string( "out" ) || cmd == string( "OUT" ) ) {
			createOUTRegs( tokens );
			return;
		}
		if( cmd == string( "inc" ) || cmd == string( "INC" ) ) {
			createINCRegs( tokens );
			return;
		}
		if( cmd == string( "dec" ) || cmd == string( "DEC" ) ) {
			createDECRegs( tokens );
			return;
		}
		if( cmd == string( "add" ) || cmd == string( "ADD" ) ) {
			createADDRegs( tokens );
			return;
		}
		if( cmd == string( "sub" ) || cmd == string( "SUB" ) ) {
			createSUBRegs( tokens );
			return;
		}
		if( cmd == string( "cmp" ) || cmd == string( "CMP" ) ) {
			createCMPRegs( tokens );
			return;
		}
		if( cmd == string( "jmp" ) || cmd == string( "JMP" ) ) {
			createJMPRegs( tokens );
			return;
		}
		if( cmd == string( "shu" ) || cmd == string( "SHU" ) ) {
			createSHURegs( tokens );
			return;
		}
		if( cmd == string( "shd" ) || cmd == string( "SHD" ) ) {
			createSHDRegs( tokens );
			return;
		}
		if( cmd == string( "outc" ) || cmd == string( "OUTC" ) ) {
			createOUTCRegs( tokens );
			return;
		}
		if( cmd == string( "stop" ) || cmd == string( "STOP" ) ) {
			createSTOPRegs( tokens );
			return;
		}
		if( cmd == string( "var" ) || cmd == string( "VAR" ) ) {
			createVARRegs( tokens );
			return;
		}
		if( cmd == string( "ret" ) || cmd == string( "RET" ) ) {
			createRETRegs( tokens );
			return;
		}
		if( cmd == string( "call" ) || cmd == string( "CALL" ) ) {
			createCALLRegs( tokens );
			return;
		}
		if( cmd == string( "push" ) || cmd == string( "PUSH" ) ) {
			createPUSHRegs( tokens );
			return;
		}
		if( cmd == string( "pop" ) || cmd == string( "POP" ) ) {
			createPOPRegs( tokens );
			return;
		}
		//if( cmd == string( "top" ) || cmd == string( "TOP" ) ) {
		//	createTOPRegs( tokens );
		//	return;
		//}
		//if( cmd == string( "je" ) || cmd == string( "JE" ) ) {
		//	createJERegs( tokens );
		//}
		//if( cmd == string( "jne" ) || cmd == string( "JNE" ) ) {
		//	createJNERegs( tokens );
		//}
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
	if( p < 101) {
		p = 101;
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
	assert( tokens.size() == 3 );
	unsigned int dst = std::stoi( tokens[1] );
	unsigned int src = std::stoi( tokens[2] );
	code.push_back( CRegs( 11, dst, src ) );
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

void CInterpreter::createSTOPRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 1 );
	code.push_back( CRegs( 15, 0, 0 ) );
}

unsigned int CInterpreter::getVar( const string & name )
{
	if( vars.find( name ) != vars.end() ) {
		return vars[name];
	}
	return unsigned int( std::stoi( name ) );
}

void CInterpreter::createVARRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 3 );
	string varName = tokens[1];
	unsigned int dst = std::stoi( tokens[2] );
	vars.insert( pair<string, unsigned int>( varName, dst ) );
	// на втором проходе src замениться на строчку в бинарнике где лежит функция
	code.push_back( CRegs( 16, dst, 0 ) );
}

unsigned int CInterpreter::getLabelId( const string & name )
{
	if( labels.find( name ) != labels.end() ) {
		return labels[name];
	}
	unsigned int id = labels.size();
	labels.insert( pair<string, unsigned int>( name, id ) );
	return id;
}

unsigned int CInterpreter::getLabelSrc( unsigned int id )
{
	if( labelsIdStr.find( id ) == labelsIdStr.end() ) {
		// вызвали функцию с несуществующим id
		assert( false );
	}
	return labelsIdStr[id];
}

void CInterpreter::restoreLabels()
{
	for( int i = 0; i < code.size(); i++ ) {
		unsigned int cmd = code[i].getCMD();
		if( cmd == 17 ) {
			unsigned int id = code[i].getSRC();
			// функция знает строчку где она находится в бинарнике
			code[i].setSRC( i );
			labelsIdStr.insert( pair<unsigned int, unsigned int>( id, i ) );
		}
		//if( cmd == 18 ) {
		//	// ret знает строчку где начинается функция уровня выше в бинарнике
		//	code[i].setSRC( i );
		//	return;
		//}
		if( cmd == 19 ) {
			unsigned int id = code[i].getSRC();
			code[i].setSRC( getLabelSrc( id ) );
		}
	}
}

void CInterpreter::createLABELRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 1 );
	unsigned int id = getLabelId( tokens[0] );
	code.push_back( CRegs(17, id, id) );
}

void CInterpreter::createRETRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 1 );
	code.push_back( CRegs( 18, 0, 0 ) );
}

void CInterpreter::createCALLRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int id = getLabelId( tokens[1] );
	code.push_back( CRegs( 19, 0, id ) );
}

void CInterpreter::createPUSHRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int src = getVar( tokens[1] ); // std::stoi( tokens[1] );
	code.push_back( CRegs( 20, 0, src ) );
}

void CInterpreter::createPOPRegs( const vector<string>& tokens )
{
	assert( tokens.size() == 2 );
	unsigned int src = getVar( tokens[1] ); // std::stoi( tokens[1] );
	code.push_back( CRegs( 21, 0, src ) );
}

//void CInterpreter::createTOPegs( const vector<string>& tokens )
//{
//	assert( tokens.size() == 2 );
//	unsigned int src = std::stoi( tokens[1] );
//	code.push_back( CRegs( 22, 0, src ) );
//}

//void CInterpreter::createJERegs( const vector<string>& tokens )
//{
//	assert( tokens.size() == 2 );
//	unsigned int src = std::stoi( tokens[1] );
//	code.push_back( CRegs( 23, 0, src ) );
//}
//
//void CInterpreter::createJNERegs( const vector<string>& tokens )
//{
//	assert( tokens.size() == 2 );
//	unsigned int src = std::stoi( tokens[1] );
//	code.push_back( CRegs( 24, 0, src ) );
//}