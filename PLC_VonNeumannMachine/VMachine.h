#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

// ������ ������ ���� 01 23 34 56 78
class CRegs {
public:
	CRegs() : cmd( 0 ), src1( 0 ), src2( 0 ), dst1( 0 ), dst2( 0 ) {}
	CRegs( unsigned int c, unsigned int s1, unsigned int s2, unsigned int d1, unsigned int d2 ) :
		cmd( c ), src1( s1 ), src2( s2 ), dst1( d1 ), dst2( d2 ) {}
	void print() 
	{ 
		cout.width( 2 );
		cout << cmd << " " << src1 << " " << src2 << " " << dst1 << " " << dst2 << endl; 
	}
	void fprint( const ofstream& fout ) { const_cast<ofstream&>(fout) << cmd << " " << src1 << " " << src2 << " " << dst1 << " " << dst2 << endl; }
private:
	// ** 00 00 00 00 �������� �������
	unsigned int cmd;
	// 00 ** 00 00 00 �������� ������ ��� ������ ������ ���������( ������ �������� )
	unsigned int src1;
	// 00 00 ** 00 00 �������� ������ ��� ������ ����� ���������( ������ �������� )
	unsigned int src2;
	// 00 00 00 ** 00 �������� ������ ��� ������ ������ ���������( ������ �������� )
	unsigned int dst1;
	// 00 00 00 00 ** �������� ������ ��� ������ ������ ���������( ������ �������� )
	unsigned int dst2;
};


class CVMachine {
public:
	CVMachine() : current( 0 ) { cout << "CVMachine ";  printCurrent(); };
	// ��������� ����-��� �� �����
	void readProgramm( const string& path );
	// ������� � ������� ���
	void printProgramm();
	// ����� ����-��� ��������� � ����
	void printCurrent() { cout << "current = " << current << endl; }
	void writeProgramm( const string& path );
	void parseCommand( const string& line );
	void createRegs( const vector<unsigned int>& tokens );

protected:
	void processIPRegs( const vector<unsigned int>& tokens );
	void processMOVRegs( const vector<unsigned int>& tokens );
	void processSETRegs( const vector<unsigned int>& tokens );
	void processINRegs( const vector<unsigned int>& tokens );
	void processOUTRegs( const vector<unsigned int>& tokens );
	void processINCRegs( const vector<unsigned int>& tokens );
	void processDECRegs( const vector<unsigned int>& tokens );
	void processADDRegs( const vector<unsigned int>& tokens );
	void processSUBRegs( const vector<unsigned int>& tokens );

	//void createJMPRegs( const vector<string>& tokens );
	//void createCALLRegs( const vector<string>& tokens );
	//void createRETRegs( const vector<string>& tokens );
	//void createLABELRegs( const vector<string>& tokens );

	void processSTOPRegs( const vector<unsigned int>& tokens );

private:
	// ����� ������� �������
	unsigned int current;
	vector<CRegs> code;
};
