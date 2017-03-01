#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

/*
коды команд :
00
01
..
FF
*/


// четрые €чейки вида FF 00 00 00
class CRegs {
public:
	CRegs() : eax( 0 ), ebx( 0 ), ecx( 0 ), edx( 0 ) {}
	CRegs(int ax, int bx, int cx, int dx) : eax( ax ), ebx( bx ), ecx( cx ), edx( dx ) {}
	void print() { cout << eax << " " << ebx << " " << ecx << " " << edx << " " << endl; }
private:
	// ** 00 00 00 кодируют команду
	unsigned char eax;
	// 00 ** 00 00 кодируют адрес применика( первый параметр )
	unsigned char ebx;
	// 00 00 ** 00 кодируют флаг true / false
	unsigned char ecx;
	// 00 00 00 ** кодируют адрес источника( второй параметр )
	unsigned char edx;
};


class CInterpreter {
public:
	// пишет байт-код программы в файл
	void writeProgramm( const string& path );
	// читает код программы на ассембелре
	void readProgramm( const string& path );
	void parseCommand( const string& line );
	const CRegs& createRegs( const vector<string>& tokens );

protected:
	const CRegs& createIPRegs( const vector<string>& tokens );
	const CRegs& createMOVRegs( const vector<string>& tokens );
	const CRegs& createINRegs( const vector<string>& tokens );
	const CRegs& createOUTRegs( const vector<string>& tokens );
	const CRegs& createINCRegs( const vector<string>& tokens );
	const CRegs& createDECRegs( const vector<string>& tokens );
	const CRegs& createJMPRegs( const vector<string>& tokens );
	const CRegs& createCALLRegs( const vector<string>& tokens );
	const CRegs& createRETRegs( const vector<string>& tokens );
	const CRegs& createLABELRegs( const vector<string>& tokens );
	const CRegs& createSTOPRegs( const vector<string>& tokens );

private:
	vector<CRegs> code;
};