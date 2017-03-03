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
	assert( tokens.size() == 5 );
	code.push_back( CRegs( tokens[0], tokens[1], tokens[2], tokens[3], tokens[4] ) );
}

void CVMachine::processProgramm()
{
	while( !stop ) {
		processRegs( code[current] );
	}
}

void CVMachine::processRegs( CRegs& regs )
{
	unsigned int cmd = regs.getCMD();
	if( cmd == 1 ) {
		processIPRegs( regs );
	}
	if( cmd == 2 ) {
		processMOVRegs( regs );
	}
	if( cmd == 3 ) {
		processSETRegs( regs );
	}
	if( cmd == 4 ) {
		processINRegs( regs );
	}
	if( cmd == 5 ) {
		processOUTRegs( regs );
	}
	if( cmd == 6 ) {
		processINCRegs( regs );
	}
	if( cmd == 7 ) {
		processDECRegs( regs );
	}
	if( cmd == 8 ) {
		processADDRegs( regs );
	}
	if( cmd == 9 ) {
		processSUBRegs( regs );
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
	if( cmd == 15 ) {
		processSTOPRegs( regs );
	}
}

//void CVMachine::processVARRegs( const vector<unsigned int>& tokens )
//{
//	assert( tokens[0] == 0 );
//	code.push_back( CRegs( tokens[0], tokens[1], tokens[2], tokens[3], tokens[4] ) );
//}

void CVMachine::processIPRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	cout << "processIPRegs ";
	printCurrent();
	current += src + 1;
}

void CVMachine::processMOVRegs( CRegs& regs )
{
	cout << "processMOVRegs ";
	printCurrent();
	current++;
}

void CVMachine::processSETRegs( CRegs& regs )
{
	unsigned int dst = regs.getDST();
	unsigned int src = regs.getSRC();
	assert( 0 < dst );
	assert( dst < code.size() );
	code[dst].setSRC( src );
	cout << "processSETRegs ";
	printCurrent();
	current++;
}

void CVMachine::processINRegs( CRegs& regs )
{
	cout << "processINRegs ";
	printCurrent();
	current++;
}

void CVMachine::processOUTRegs( CRegs& regs )
{
	cout << "processOUTRegs ";
	printCurrent();
	current++;
}

void CVMachine::processINCRegs( CRegs& regs )
{
	cout << "processINCRegs ";
	printCurrent();
	current++;
}

void CVMachine::processDECRegs( CRegs& regs )
{
	cout << "processDECRegs ";
	printCurrent();
	current++;
}

void CVMachine::processADDRegs( CRegs& regs )
{
	cout << "processADDRegs ";
	printCurrent();
	current++;
}

void CVMachine::processSUBRegs( CRegs& regs )
{
	cout << "processSUBRegs ";
	printCurrent();
	current++;
}



void CVMachine::processSTOPRegs( CRegs& regs )
{
	cout << "processSTOPRegs ";
	printCurrent();
	current++;
	stop = true;
}
