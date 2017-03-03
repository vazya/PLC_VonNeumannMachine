#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

// ������ ������ ���� 01 23 34 56 78
class CRegs {
public:
	CRegs() : cmd( 0 ), src1( 0 ), src2( 0 ), dst1( 0 ), dst2( 0 ) {}
	CRegs( unsigned int c, unsigned int s1, unsigned int s2, unsigned int d1, unsigned int d2 ) :
		cmd( c ), src1( s1 ), src2( s2 ), dst1( d1 ), dst2( d2 )
	{
	}
	void print() { cout << cmd << " " << src1 << " " << src2 << " " << dst1 << " " << dst2 << endl; }
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
	// ��������� ����-��� �� �����
	void readProgramm( const string& path );
	// ������� � ������� ���
	void printProgramm();
	// ����� ����-��� ��������� � ����
	void writeProgramm( const string& path );

private:
	vector<CRegs> code;
};
