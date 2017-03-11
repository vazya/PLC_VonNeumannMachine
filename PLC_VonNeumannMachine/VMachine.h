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
	void setDST( unsigned int d ) { dst = d; }
	void setCMD( unsigned int c ) { cmd = c; }
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
	CVMachine() : instructionPointer( 17 ), stackStart(5), stackPointer(5),
			retPointer(0), callStackStart(10), callStackPointer(10), comparePointer(1)
	{ /*cout << "CVMachine ";  printCurrent();*/ };
	// считывает байт-код из фалйа
	void readProgramm( const string& path );
	// выполн€ет программу
	void processProgramm();
	// выводит в консоль код
	void printProgramm();
	void readByteCode( const string & path );
	// пишет байт-код программы в файл
	void printIP() { cout << "instrictionPointer = " << instructionPointer << endl; }
	void printSP() { cout << "stackPointer = " << stackPointer << endl; }
	void printCSP() { cout << "callStackPointer = " << callStackPointer << endl; }

	void writeProgramm( const string& path );
	void parseCommand( const string& line );
	// наивна€ проверка указателей
	void check( unsigned int arg ) { assert( 0 <= arg ); assert( arg < code.size() ); }
protected:
	void processRegs( CRegs& regs );
	void processMEMRegs( CRegs& regs );
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
	void processOUTCRegs( CRegs& regs );

	void processSTOPRegs( CRegs& regs );

	void processVARRegs( CRegs& regs );
	void processLABELRegs( CRegs& regs );
	void processRETRegs( CRegs& regs );
	void processCALLRegs( CRegs& regs );

	void processPUSHRegs( CRegs& regs );
	void processPOPRegs( CRegs& regs );

private:
	void setIP( unsigned int newIP );
	unsigned int getIP();
	void incIP( unsigned int shift = 1 );
	void decIP( unsigned int shift = 1 );

	void setSP( unsigned int newSP );
	unsigned int getSP();
	void incSP( unsigned int shift = 1 );
	void decSP( unsigned int shift = 1 );

	void pushStack( unsigned int src );
	void popStack( unsigned int dst );
	unsigned int topStack();

	void setRetPointer( unsigned int src );
	unsigned int getRetPointer();

	void setCSP( unsigned int newCSP );
	unsigned int getCSP();
	void incCSP( unsigned int shift = 1 );
	void decCSP( unsigned int shift = 1 );

	void pushCallStack( unsigned int src );
	void popCallStack();
	unsigned int topCallStack();

	void setCP( bool equal );
	bool getCP();

	// номер текущей команды
	unsigned int instructionPointer;
	// начало стека
	unsigned int stackStart;
	// указатель на верхушку стека
	unsigned int stackPointer;
	// зарезервированна€ €чейка под возвращаемое значение
	unsigned int retPointer;
	// в call-стек складываем вызывающую функцию
	// начало call-стека
	unsigned int callStackStart;
	// указатель на начало call-стека
	unsigned int callStackPointer;

	unsigned int comparePointer;

	vector<CRegs> code;
};
