#include "VMachine.h"

void CVMachine::setIP( unsigned int newIP )
{
	//instructionPointer = newIP;
	code[1].setSRC( newIP ); 
}

unsigned int CVMachine::getIP()
{
	//return instructionPointer;
	return code[1].getSRC();
}

void CVMachine::incIP( unsigned int shift )
{
	//instructionPointer += shift;
	setIP( getIP() + shift );
}

void CVMachine::decIP( unsigned int shift )
{
	//instructionPointer -= shift;
	setIP( getIP() - shift );
}

void CVMachine::setSP( unsigned int newSP )
{
	//stackPointer = newSP;
	code[10].setSRC( newSP );
}

unsigned int CVMachine::getSP()
{
	//return stackPointer;
	return code[10].getSRC();
}

void CVMachine::incSP( unsigned int shift )
{
	//stackPointer += shift;
	setSP( getSP() + shift );
}

void CVMachine::decSP( unsigned int shift )
{
	//stackPointer -= shift;
	setSP( getSP() - shift );
}

void CVMachine::pushStack( unsigned int src )
{
	incSP();
	//code[stackPointer].setSRC( src );
	code[getSP()].setSRC( src );
}

void CVMachine::popStack( unsigned int dst )
{
	//unsigned int src = topStack();
	//code[dst].setSRC( src );
	code[dst].setSRC( topStack() );
	decSP();
}

unsigned int CVMachine::topStack()
{
	//return code[stackPointer].getSRC();
	return code[getSP()].getSRC();
}

void CVMachine::setRetPointer( unsigned int src )
{
	//retPointer = src;
	code[2].setSRC( src );
}

unsigned int CVMachine::getRetPointer()
{
	//return retPointer;
	return code[2].getSRC();
}

void CVMachine::setCSP( unsigned int newCSP )
{
	callStackPointer = newCSP;
}

unsigned int CVMachine::getCSP()
{
	return callStackPointer;
}

void CVMachine::incCSP( unsigned int shift )
{
	callStackPointer += shift;
}

void CVMachine::decCSP( unsigned int shift )
{
	callStackPointer -= shift;
}

void CVMachine::pushCallStack( unsigned int src )
{
	incCSP();
	code[callStackPointer].setSRC( src );
}

void CVMachine::popCallStack()
{
	code[callStackPointer].setSRC( 0 );
	decCSP();
}

unsigned int CVMachine::topCallStack()
{
	return code[callStackPointer].getSRC();
}

void CVMachine::setCP( bool equal )
{
	if( equal ) {
		code[3].setDST( 1 );
		code[3].setSRC( 0 );
	} else {
		code[3].setDST( 0 );
		code[3].setSRC( 1 );
	}
}

bool CVMachine::getCP()
{
	if( code[3].getDST() == 1 && code[3].getSRC() == 0 ) {
		return true;
	}
	return false;
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
		code.push_back( CRegs( cmd, dst, src ) );
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

string CVMachine::disasmblyCMD( unsigned int cmd )
{
	string cmdStr;
	switch( cmd ) {
		case 1:
			cmdStr = string( "ip" );
			break;
		case 2:
			cmdStr = string( "mov" );
			break;
		case 3:
			cmdStr = string( "set" );
			break;
		case 4:
			cmdStr = string( "in" );
			break;
		case 5:
			cmdStr = string( "out" );
			break;
		case 6:
			cmdStr = string( "inc" );
			break;
		case 7:
			cmdStr = string( "dec" );
			break;
		case 8:
			cmdStr = string( "add" );
			break;
		case 9:
			cmdStr = string( "sub" );
			break;
		case 10:
			cmdStr = string( "cmp" );
			break;
		case 11:
			cmdStr = string( "jmp" );
			break;
		case 12:
			cmdStr = string( "shu" );
			break;
		case 13:
			cmdStr = string( "shd" );
			break;
		case 14:
			cmdStr = string( "outc" );
			break;
		case 15:
			cmdStr = string( "stop" );
			break;
		case 16:
			cmdStr = string( "var" );
			break;
		case 17:
			cmdStr = string( "@label" );
			break;
		case 18:
			cmdStr = string( "ret" );
			break;
		case 19:
			cmdStr = string( "call" );
			break;
		case 20:
			cmdStr = string( "push" );
			break;
		case 21:
			cmdStr = string( "pop" );
			break;
	}
	return cmdStr;
}


void CVMachine::disasemblyByteCode( const string & path )
{
	ofstream fout( path );
	unsigned int numOfTab = 0;
	for( int i = 0; i < code.size(); i++ ) {
		unsigned int cmd = code[i].getCMD();
		if( cmd != 0 ) {
			string cmdStr = disasmblyCMD( cmd );
			unsigned int dst = code[i].getDST();
			unsigned int src = code[i].getSRC();
			for( unsigned int j = 0; j < numOfTab; j++ ) {
				fout << '	';
			}
			fout << cmdStr << " " << dst << " " << src << endl;
		}
		if( cmd == 17 ) {
			numOfTab++;
		}
		if( cmd == 18 ) {
			numOfTab--;
		}
	}
	fout.close();
}

void CVMachine::readProgramm( const string & path )
{
	string line;
	fstream file( path );

	while( getline( file, line ) ) {
		if( !line.empty() ) {
			parseCommand( line );
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
		while( c != '\0' && c != ' ' && c != '\n' && c != '\r' ) {
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
	setIP( 0 );
	setSP( 10 );
	while( getIP() /*instructionPointer*/ < code.size() ) {
		//processRegs( code[instructionPointer] );
		processRegs( code[getIP()] );
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
	incIP(); // instructionPointer++;
}

void CVMachine::processVARRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );
	incIP(); // instructionPointer++;
}

void CVMachine::processIPRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );
	incIP( src + 1 ); // instructionPointer += src + 1;
}

void CVMachine::processMOVRegs( CRegs& regs )
{
	unsigned int dst = regs.getDST();
	check( dst );
	unsigned int src = regs.getSRC();
	check( src );

	unsigned int data = code[src].getSRC();
	code[dst].setSRC( data );

	incIP(); // instructionPointer++;
}

void CVMachine::processSETRegs( CRegs& regs )
{
	unsigned int dst = regs.getDST();
	unsigned int src = regs.getSRC();
	check( dst );

	code[dst].setSRC( src );

	incIP(); // instructionPointer++;
}

void CVMachine::processINRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();

	unsigned int data = 0;
	cin >> data;
	code[src].setSRC( data );

	incIP(); // instructionPointer++;
}

void CVMachine::processOUTRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );

	unsigned int data = code[src].getSRC();
	cout << data << endl;

	incIP(); // instructionPointer++;
}

void CVMachine::processINCRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );

	unsigned int data = code[src].getSRC();
	code[src].setSRC( data + 1 );

	incIP(); // instructionPointer++;
}

void CVMachine::processDECRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );

	unsigned int data = code[src].getSRC();
	code[src].setSRC( data - 1 );

	incIP(); // instructionPointer++;
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

	incIP(); // instructionPointer++;
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

	incIP(); // instructionPointer++;
}

void CVMachine::processCMPRegs( CRegs& regs )
{
	unsigned int dst = regs.getDST();
	check( dst );
	unsigned int src = regs.getSRC();
	check( src );

	unsigned int dstData = code[dst].getSRC();
	unsigned int srcData = code[src].getSRC();
	setCP( dstData == srcData );

	incIP(); // instructionPointer++;
}

void CVMachine::processJMPRegs( CRegs& regs )
{
	unsigned int dst = regs.getDST();
	check( dst );
	unsigned int src = regs.getSRC();
	check( src );

	if( getCP() ) {
		setIP( dst ); // instructionPointer = dst;
	} else {
		setIP( src ); // instructionPointer = src;
	}
}

void CVMachine::processSHURegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );
	check( getIP() - src );

	decIP( src ); // instructionPointer -= src;
}

void CVMachine::processSHDRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );
	check( getIP() + src );

	incIP( src ); // instructionPointer += src;
}

void CVMachine::processOUTCRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	cout << char( src );

	incIP(); // instructionPointer++;
}

void CVMachine::processSTOPRegs( CRegs& regs )
{
	incIP(); // instructionPointer++;
}

void CVMachine::processLABELRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );
	unsigned int dst = regs.getDST();

	incIP(); // instructionPointer++;
}

void CVMachine::processRETRegs( CRegs& regs )
{
	// возвращает нас к предыдущей инструкции и сдвигается на одну вниз
	//setIP( getRetPointer() );
	setIP( topCallStack() );
	popCallStack();
	incIP(); // instructionPointer++;
}

void CVMachine::processCALLRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );

	// запомнили где находились до обработки call
	//setRetPointer( getIP() );
	pushCallStack( getIP() );

	// установили текущей выполняемой инструкцией - строчку где лежит функция
	setIP( src );
	incIP(); // processRegs( code[getIP()] );
}

void CVMachine::processPUSHRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );

	unsigned int data = code[src].getSRC();
	pushStack( data );

	incIP(); // instructionPointer++;
}

void CVMachine::processPOPRegs( CRegs& regs )
{
	unsigned int src = regs.getSRC();
	check( src );

	popStack( src );

	incIP(); // instructionPointer++;
}