#include "VMachine.h"

void CVMachine::printProgramm()
{
	for( int i = 0; i < code.size(); i++ ) {
		cout.width( 2 );
		cout << i << " : ";
		code[i].print();
	}
	printCurrent();
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
			parseCommand(line);
		}
	}
	file.close();
}

void CVMachine::parseCommand( const string & line )
{
	// пилим строку на токены
	vector<unsigned int> tokens;
	int counter = 0;
	while( counter < line.length() ) {
		string token;
		char c = line[counter];
		while( c != '\0' && c != ' ' && c != '\n' && c != '\r') {
			token.push_back( c );
			counter++;
			c = line[counter];
		}
		if( !token.empty() ) {
			unsigned int ip = stoi( token );
			token.clear();
			tokens.push_back( ip );
		}
		counter++;
	}
	createRegs( tokens );
}

void CVMachine::createRegs( const vector<unsigned int>& tokens )
{
	assert( tokens.size() == 5 );
	code.push_back( CRegs( tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]) );
	if( tokens[0] == 1 ) {
		processIPRegs( tokens );
	}
	if( tokens[0] == 2 ) {
		processMOVRegs( tokens );
	}
	if( tokens[0] == 3 ) {
		processSETRegs( tokens );
	}
	if( tokens[0] == 4 ) {
		processINRegs( tokens );
	}
	if( tokens[0] == 5 ) {
		processOUTRegs( tokens );
	}
	if( tokens[0] == 6 ) {
		processINCRegs( tokens );
	}
	if( tokens[0] == 7 ) {
		processDECRegs( tokens );
	}
	if( tokens[0] == 8 ) {
		processADDRegs( tokens );
	}
	if( tokens[0] == 9 ) {
		processSUBRegs( tokens );
	}
	//if( tokens[0] == string( "jmp" ) || tokens[0] == string( "JMP" ) ) {
	//	processJMPRegs( tokens );
	//}
	//if( tokens[0] == string( "call" ) || tokens[0] == string( "CALL" ) ) {
	//	processCALLRegs( tokens );
	//}
	//if( tokens[0] == string( "ret" ) || tokens[0] == string( "RET" ) ) {
	//	processRETRegs( tokens );
	//}
	//if( tokens[0] == string( "label" ) || tokens[0] == string( "LABEL" ) ) {
	//	processLABELRegs( tokens );
	//}
	if( tokens[0] == 15 ) {
		processSTOPRegs( tokens );
	}
}

void CVMachine::processIPRegs( const vector<unsigned int>& tokens )
{
	unsigned int src = tokens[4];
	current += src;
	cout << "processIPRegs ";
	printCurrent();
}

void CVMachine::processMOVRegs( const vector<unsigned int>& tokens )
{
}

void CVMachine::processSETRegs( const vector<unsigned int>& tokens )
{
}

void CVMachine::processINRegs( const vector<unsigned int>& tokens )
{
}

void CVMachine::processOUTRegs( const vector<unsigned int>& tokens )
{
}

void CVMachine::processINCRegs( const vector<unsigned int>& tokens )
{
}

void CVMachine::processDECRegs( const vector<unsigned int>& tokens )
{
}

void CVMachine::processADDRegs( const vector<unsigned int>& tokens )
{
}

void CVMachine::processSUBRegs( const vector<unsigned int>& tokens )
{
}



void CVMachine::processSTOPRegs( const vector<unsigned int>& tokens )
{
}
