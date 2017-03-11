#include "VMachine.h"

void CVMachine::setIP( unsigned int newIP )
{
	instructionPointer = newIP;
}

unsigned int CVMachine::getIP()
{
	return instructionPointer;
}

void CVMachine::incIP( unsigned int shift )
{
	instructionPointer += shift;
}

void CVMachine::decIP( unsigned int shift )
{
	instructionPointer -= shift;
}

void CVMachine::setSP( unsigned int newSP )
{
	stackPointer = newSP;
}

unsigned int CVMachine::getSP()
{
	return stackPointer;
}

void CVMachine::incSP( unsigned int shift )
{
	stackPointer += shift;
}

void CVMachine::decSP( unsigned int shift )
{
	stackPointer -= shift;
}

void CVMachine::push( unsigned int src )
{
	code[stackPointer].setSRC( src );
	incSP();
}

void CVMachine::pop( unsigned int dst )
{
	unsigned int src = top();
	code[dst].setSRC( src );
	decSP();
}

unsigned int CVMachine::top()
{
	return code[stackPointer].getSRC();
}

void CVMachine::printProgramm()
{
	for( int i = 0; i < code.size(); i++ ) {
		cout.width( 2 );
		cout << i << " : ";
		code[i].print();
	}
	printIP();
	system( "pause" );
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
	// ���� ��� ���������� �� ������� ����
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
	// ����� ������ �� ������
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
	while( instructionPointer > 0 ) {
		processRegs( code[instructionPointer] );
		//printProgramm();
	}
}

void CVMachine::processRegs( CRegs& regs )
{
	unsigned int cmd = regs.getCMD();
	if( cmd == 0 ) {
		processMEMRegs( regs );
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
	if( cmd == 15 ) {
		processSTOPRegs( regs );
	}
	if( cmd == 16 ) {
		processVARRegs( regs );
	}
	if( cmd == 17 ) {
		processLABELRegs( regs );
	}
	if( cmd == 18 ) {
		processRETRegs( regs );
	}
	if( cmd == 19 ) {
		processCALLRegs( regs );
	}
	if( cmd == 20 ) {
		processPUSHRegs( regs );
	}
	if( cmd == 21 ) {
		processPOPRegs( regs );
	}
}

void CVMachine::processMEMRegs( CRegs & regs )
{
	cout << "reach memory" << endl;
	instructionPointer++;
}

void CVMachine::processVARRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );
	//cout << "processVARRegs ";
	//printCurrent();
	instructionPointer++;
}

void CVMachine::processIPRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );
	//cout << "processIPRegs ";
	//printCurrent();
	instructionPointer += src + 1;
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
	instructionPointer++;
}

void CVMachine::processSETRegs( CRegs& regs )
{
	unsigned int dst = regs.getDST();
	unsigned int src = regs.getSRC();
	check( dst );

	code[dst].setSRC( src );

	//cout << "processSETRegs ";
	//printCurrent();
	instructionPointer++;
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
	instructionPointer++;
}

void CVMachine::processOUTRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );

	unsigned int data = code[src].getSRC();
	cout << data << endl;

	//cout << "processOUTRegs ";
	//printCurrent();
	instructionPointer++;
}

void CVMachine::processINCRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );

	unsigned int data = code[src].getSRC();
	code[src].setSRC(data + 1);

	//cout << "processINCRegs ";
	//printCurrent();
	instructionPointer++;
}

void CVMachine::processDECRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );

	unsigned int data = code[src].getSRC();
	code[src].setSRC( data - 1 );

	//cout << "processDECRegs ";
	//printCurrent();
	instructionPointer++;
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
	instructionPointer++;
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
	instructionPointer++;
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
		instructionPointer++;
	}

	//cout << "processCMPRegs ";
	//printCurrent();
	instructionPointer++;
}

void CVMachine::processJMPRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );

	//cout << "processJMPRegs ";
	//printCurrent();

	instructionPointer = src;
}

void CVMachine::processSHURegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );
	check( instructionPointer - src );

	//cout << "processSHURegs ";
	//printCurrent();

	instructionPointer -= src;
}

void CVMachine::processSHDRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );
	check( instructionPointer + src );

	//cout << "processSHDRegs ";
	//printCurrent();

	instructionPointer += src;
}

void CVMachine::processOUTCRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	cout << char( src );

	//cout << "processOUTCRegs ";
	//printCurrent();
	instructionPointer++;
}

void CVMachine::processSTOPRegs( CRegs& regs )
{
	//cout << "processSTOPRegs ";
	//printCurrent();

	instructionPointer = 0;
}

void CVMachine::processLABELRegs( CRegs& regs )
{
	//unsigned int src = regs.getSRC();
	//cout << char( src );

	//cout << "processLABELRegs ";
	//printCurrent();
	instructionPointer++;
}

void CVMachine::processRETRegs( CRegs& regs )
{
	//unsigned int src = regs.getSRC();
	//cout << char( src );

	//cout << "processRETRRegs ";
	//printCurrent();
	instructionPointer++;
}

void CVMachine::processCALLRegs( CRegs& regs )
{
	//unsigned int src = regs.getSRC();
	//cout << char( src );

	//cout << "processCALLRegs ";
	//printCurrent();
	instructionPointer++;
}

void CVMachine::processPUSHRegs( CRegs& regs )
{
	//unsigned int src = regs.getSRC();
	//cout << char( src );

	//cout << "processCALLRegs ";
	//printCurrent();
	instructionPointer++;
}

void CVMachine::processPOPRegs( CRegs& regs )
{
	//unsigned int src = regs.getSRC();
	//cout << char( src );

	//cout << "processCALLRegs ";
	//printCurrent();
	instructionPointer++;
}