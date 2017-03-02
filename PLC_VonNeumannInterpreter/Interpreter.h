#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

// четрые €чейки вида 01 23 34 56 78
class CRegs {
public:
	CRegs() : cmd( 0 ), src1( 0 ), src2( 0 ), dst1( 0 ), dst2( 0 ) {}
	CRegs( unsigned int c, unsigned int s1, unsigned int s2, unsigned int d1, unsigned int d2 ) :
			cmd( c ), src1( s1 ), src2( s2 ), dst1( d1 ), dst2( d2 ) {}
	void print() { cout << cmd << " " << src1 << " " << src2 << " " << dst1 << " " << dst2 << endl; }
private:
	// ** 00 00 00 00 кодируют команду
	unsigned int cmd;
	// 00 ** 00 00 00 кодируют первые две €чейки адреса применика( первый параметр )
	unsigned int src1;
	// 00 00 ** 00 00 кодируют вторые две €чейки адрес применика( первый параметр )
	unsigned int src2;
	// 00 00 00 ** 00 кодируют первые две €чейки адреса источника( второй параметр )
	unsigned int dst1;
	// 00 00 00 00 ** кодируют вторые две €чейки адреса источника( второй параметр )
	unsigned int dst2;
};


class CInterpreter {
public:
	// выводит в консоль код
	void printProgramm();
	// пишет байт-код программы в файл
	void writeProgramm( const string& path );
	// читает код программы на ассембелре
	void readProgramm( const string& path );
	void parseCommand( const string& line );
	void createRegs( const vector<string>& tokens );

protected:
	void createIPRegs( const vector<string>& tokens );
	void createMOVRegs( const vector<string>& tokens );
	void createSETRegs( const vector<string>& tokens );
	void createINRegs( const vector<string>& tokens );
	void createOUTRegs( const vector<string>& tokens );
	void createINCRegs( const vector<string>& tokens );
	void createDECRegs( const vector<string>& tokens );
	void createJMPRegs( const vector<string>& tokens );
	void createCALLRegs( const vector<string>& tokens );
	void createRETRegs( const vector<string>& tokens );
	void createLABELRegs( const vector<string>& tokens );
	void createSTOPRegs( const vector<string>& tokens );

private:
	vector<CRegs> code;
};