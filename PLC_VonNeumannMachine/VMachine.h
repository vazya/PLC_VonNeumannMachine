#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

// четрые €чейки вида 01 23 34 56 78
class CRegs {
public:
	CRegs() : cmd( 0 ), dst1( 0 ), dst2( 0 ), src1( 0 ), src2( 0 ) {}
	CRegs( unsigned int c, unsigned int d1, unsigned int d2, unsigned int s1, unsigned int s2 ) :
		cmd( c ), dst1( d1 ), dst2( d2 ), src1( s1 ), src2( s2 ) {}
	void print() 
	{ 
		cout.width( 2 );
		cout << cmd << " " << dst1 << " " << dst2 << " " << src1 << " " << src2 << endl;
	}
	void fprint( const ofstream& fout ) { const_cast<ofstream&>(fout) << cmd << " " << dst1 << " " << dst2 << " " << src1 << " " << src2 << endl; }
	void setSRC( unsigned int src ) { src2 = src; }
	void setDST( unsigned int dst ) { assert( false ); }
	void setCMD( unsigned int cmd ) { assert( false ); }
	unsigned int  getCMD() const { return cmd; }
	unsigned int  getDST() const { return dst2; }
	unsigned int  getSRC() const { return src2; }
private:
	// ** 00 00 00 00 кодируют команду
	unsigned int cmd;
	// 00 ** 00 00 00 кодируют первые две €чейки адреса применика( первый параметр )
	unsigned int dst1;
	// 00 00 ** 00 00 кодируют вторые две €чейки адрес применика( первый параметр )
	unsigned int dst2;
	// 00 00 00 ** 00 кодируют первые две €чейки адреса источника( второй параметр )
	unsigned int src1;
	// 00 00 00 00 ** кодируют вторые две €чейки адреса источника( второй параметр )
	unsigned int src2;
};


class CVMachine {
public:
	CVMachine() : current( 0 ), stop(false) { cout << "CVMachine ";  printCurrent(); };
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

protected:
	void processRegs( CRegs& regs );
	//void processVARRegs( const vector<unsigned int>& tokens );
	void processIPRegs( CRegs& regs );
	void processMOVRegs( CRegs& regs );
	void processSETRegs( CRegs& regs );
	void processINRegs( CRegs& regs );
	void processOUTRegs( CRegs& regs );
	void processINCRegs( CRegs& regs );
	void processDECRegs( CRegs& regs );
	void processADDRegs( CRegs& regs );
	void processSUBRegs( CRegs& regs );

	//void createJMPRegs( const vector<string>& tokens );
	//void createCALLRegs( const vector<string>& tokens );
	//void createRETRegs( const vector<string>& tokens );
	//void createLABELRegs( const vector<string>& tokens );

	void processSTOPRegs( CRegs& regs );

private:
	bool stop;
	// номер текущей команды
	unsigned int current;
	vector<CRegs> code;
};
