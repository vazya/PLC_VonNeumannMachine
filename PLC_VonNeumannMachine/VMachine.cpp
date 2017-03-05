#include "VMachine.h"

void CVMachine::printProgramm()
{
	for( int i = 0; i < code.size(); i++ ) {
		cout.width( 2 );
		cout << i << " : ";
		code[i].print();
	}
	printCurrent();
	cout << "code.size = " << code.size() << endl;
}

void CVMachine::readByteCode( const string & path )
{
	ifstream fin( path, ios::binary | ios::in );
	unsigned int cmd, dst, src;
	do {
		fin.read( (char*)&cmd, sizeof cmd );
		fin.read( (char*)&dst, sizeof dst );
		fin.read( (char*)&src, sizeof src );
		code.push_back( CRegs(cmd, dst, src) );
	} while( cmd != unsigned int( 15 ) );
	fin.close();
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
	assert( tokens.size() == 3 );
	code.push_back( CRegs( tokens[0], tokens[1], tokens[2] ) );
}

void CVMachine::processProgramm()
{
	while( current > 0 ) {
		processRegs( code[current] );
		//printProgramm();
		//system( "pause" );
	}
}

void CVMachine::processRegs( CRegs& regs )
{
	unsigned int cmd = regs.getCMD();
	if( cmd == 0 ) {
		processVARRegs( regs );
	}
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
	if( cmd == 10 ) {
		processCMPRegs( regs );
	}
	if( cmd == 11 ) {
		processJMPRegs( regs );
	}
	if( cmd == 12 ) {
		processSHURegs( regs );
	}
	if( cmd == 13 ) {
		processSHDRegs( regs );
	}
	if( cmd == 14 ) {
		processOUTCRegs( regs );
	}
	if( cmd == 15 ) {
		processSTOPRegs( regs );
	}
}

void CVMachine::processVARRegs( CRegs& regs )
{
	cout << "programm reach vars" << endl;
	processSTOPRegs( regs );
}

void CVMachine::processIPRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );
	//cout << "processIPRegs ";
	//printCurrent();
	current += src + 1;
}

void CVMachine::processMOVRegs( CRegs& regs )
{
	unsigned int dst = regs.getDST();
	check( dst );
	unsigned int src = regs.getSRC();
	check( src );
	
	unsigned int data = code[src].getSRC();
	code[dst].setSRC( data );

	//cout << "processMOVRegs ";
	//printCurrent();
	current++;
}

void CVMachine::processSETRegs( CRegs& regs )
{
	unsigned int dst = regs.getDST();
	unsigned int src = regs.getSRC();
	check( dst );

	code[dst].setSRC( src );

	//cout << "processSETRegs ";
	//printCurrent();
	current++;
}

void CVMachine::processINRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	
	unsigned int data = 0;
	//cout << "enter number ples = ";
	cin >> data;
	code[src].setSRC( data );

	//cout << "processINRegs ";
	//printCurrent();
	current++;
}

void CVMachine::processOUTRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );

	unsigned int data = code[src].getSRC();
	cout << data;

	//cout << "processOUTRegs ";
	//printCurrent();
	current++;
}

void CVMachine::processINCRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );

	unsigned int data = code[src].getSRC();
	code[src].setSRC(data + 1);

	//cout << "processINCRegs ";
	//printCurrent();
	current++;
}

void CVMachine::processDECRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );

	unsigned int data = code[src].getSRC();
	code[src].setSRC( data - 1 );

	//cout << "processDECRegs ";
	//printCurrent();
	current++;
}

void CVMachine::processADDRegs( CRegs& regs )
{
	unsigned int dst = regs.getDST();
	check( dst );
	unsigned int src = regs.getSRC();
	check( src );

	unsigned int dstData = code[dst].getSRC();
	unsigned int srcData = code[src].getSRC();
	code[dst].setSRC( dstData + srcData );

	//cout << "processADDRegs ";
	//printCurrent();
	current++;
}

void CVMachine::processSUBRegs( CRegs& regs )
{
	unsigned int dst = regs.getDST();
	check( dst );
	unsigned int src = regs.getSRC();
	check( src );

	unsigned int dstData = code[dst].getSRC();
	unsigned int srcData = code[src].getSRC();
	code[dst].setSRC( dstData - srcData );

	//cout << "processSUBRegs ";
	//printCurrent();
	current++;
}

void CVMachine::processCMPRegs( CRegs& regs )
{
	unsigned int dst = regs.getDST();
	check( dst );
	unsigned int src = regs.getSRC();
	check( src );

	unsigned int dstData = code[dst].getSRC();
	unsigned int srcData = code[src].getSRC();
	if( dstData == srcData) {
		current++;
	}

	//cout << "processCMPRegs ";
	//printCurrent();
	current++;
}

void CVMachine::processJMPRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );

	//cout << "processJMPRegs ";
	//printCurrent();

	current = src;
}

void CVMachine::processSHURegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );
	check( current - src );

	//cout << "processSHURegs ";
	//printCurrent();

	current -= src;
}

void CVMachine::processSHDRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );
	check( current + src );

	//cout << "processSHDRegs ";
	//printCurrent();

	current += src;
}

void CVMachine::processOUTCRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	cout << char( src );

	//cout << "processOUTCRegs ";
	//printCurrent();
	current++;
}

void CVMachine::processSTOPRegs( CRegs& regs )
{
	//cout << "processSTOPRegs ";
	//printCurrent();

	current = 0;
}
