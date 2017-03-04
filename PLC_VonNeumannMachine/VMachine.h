#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

// три €чейки вида 01 04 05
class CRegs {
public:
	CRegs() : cmd( 0 ), dst( 0 ), src( 0 ) {}
	CRegs( unsigned int c, unsigned int d, unsigned int s ) :
		cmd( c ), dst( d ), src( s ) {}
	void print() 
	{ 
		cout.width( 2 );
		cout << cmd << " " << dst << " " << src << endl;
	}
	void fprint( const ofstream& fout ) { const_cast<ofstream&>(fout) << cmd << " " << dst << " " << src << endl; }
	void setSRC( unsigned int s ) { src = s; }
	void setDST( unsigned int d ) { assert( false ); }
	void setCMD( unsigned int c ) { assert( false ); }
	unsigned int  getCMD() const { return cmd; }
	unsigned int  getDST() const { return dst; }
	unsigned int  getSRC() const { return src; }
private:
	// ** 00 00 кодируют команду
	unsigned int cmd;
	// 00 ** 00 кодируют вторые две €чейки адрес применика( первый параметр )
	unsigned int dst;
	// 00 00 ** кодируют вторые две €чейки адреса источника( второй параметр )
	unsigned int src;
};


class CVMachine {
public:
	CVMachine() : current( 11 ) { cout << "CVMachine ";  printCurrent(); };
	// считывает байт-код из фалйа
	void readProgramm( const string& path );
	// выполн€ет программу
	void processProgramm();
	// выводит в консоль код
	void printProgramm();
	// пишет байт-код программы в файл
	void printCurrent() { cout << "current = " << current << endl; }
	void writeProgramm( const string& path );
	void parseCommand( const string& line );
	// наивна€ проверка указателей
	void check( unsigned int arg ) { assert( 0 <= arg ); assert( arg < code.size() ); }
protected:
	void processRegs( CRegs& regs );
	void processVARRegs( CRegs& regs );
	void processIPRegs( CRegs& regs );
	void processMOVRegs( CRegs& regs );
	void processSETRegs( CRegs& regs );
	void processINRegs( CRegs& regs );
	void processOUTRegs( CRegs& regs );
	void processINCRegs( CRegs& regs );
	void processDECRegs( CRegs& regs );
	void processADDRegs( CRegs& regs );
	void processSUBRegs( CRegs& regs );
	void processCMPRegs( CRegs& regs );
	void processJMPRegs( CRegs& regs );
	void processSHURegs( CRegs& regs );
	void processSHDRegs( CRegs& regs );

	//void createCALLRegs( const vector<string>& tokens );
	//void createRETRegs( const vector<string>& tokens );
	//void createLABELRegs( const vector<string>& tokens );

	void processSTOPRegs( CRegs& regs );

private:
	// номер текущей команды
	unsigned int current;
	vector<CRegs> code;
};
