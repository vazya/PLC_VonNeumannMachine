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
	system( "pause" );
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
	assert( tokens.size() == 5 );
	code.push_back( CRegs( tokens[0], tokens[1], tokens[2], tokens[3], tokens[4] ) );
}

void CVMachine::processProgramm()
{
	while( !stop ) {
		processRegs( code[current] );
		//printProgramm();
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
	//if( cmd == 11 ) {
	//	processJMPRegs( regs );
	//}
	if( cmd == 12 ) {
		processREPRegs( regs );
	}
	if( cmd == 15 ) {
		processSTOPRegs( regs );
	}
}

void CVMachine::processVARRegs( CRegs& regs )
{
	cout << "ERROR programm reach vars" << endl;
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
	cout << "enter number ples = ";
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
	cout << "result = " <<  data << endl;

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

void CVMachine::processREPRegs( CRegs& regs )
{
	unsigned int dst = regs.getDST();
	check( dst );
	unsigned int src = regs.getSRC();
	check( src );
	
	unsigned int oldCurrent = current;
	// �������� ��� �� �� ������ �� ������� ���������
	check( current + dst );

	for( unsigned int i = 0; i < src; i++ ) {
		for( unsigned j = oldCurrent + 1; j < oldCurrent + dst + 1; j++ ) {
			current = j;
			processRegs( code[j] );
			//printProgramm();
		}
	}

	//cout << "processREPRegs ";
	//printCurrent();
	current = oldCurrent + dst + 1;
}

//void CVMachine::processJMPRegs( CRegs& regs )
//{
//	unsigned int src = regs.getSRC();
//	check( src );
//
//	//cout << "processSUBRegs ";
//	//printCurrent();
//
//	current = src;
//}

void CVMachine::processSTOPRegs( CRegs& regs )
{
	//cout << "processSTOPRegs ";
	//printCurrent();
	current++;
	stop = true;
}
