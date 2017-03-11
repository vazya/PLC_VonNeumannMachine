#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
using namespace std;

// ������ ������ ���� 01 03 05
class CRegs {
public:
	CRegs() : cmd( 0 ), dst( 0 ), src( 0 ) {}
	CRegs( unsigned int c, unsigned int d, unsigned int s ) :
		cmd( c ), dst( d ), src( s )
	{
	}
	void print()
	{
		cout.width( 2 );
		cout << cmd << " " << dst << " " << src << endl;
	}
	void fprint( const ofstream& fout ) { const_cast<ofstream&>(fout) << cmd << " " << dst << " " << src << endl; }
	void setSRC( unsigned int s ) { src = s; }
	void setDST( unsigned int d ) { dst = d; }
	void setCMD( unsigned int c ) { cmd = c; }
	void setVAR( unsigned int var ) { src = var; }
	unsigned int  getCMD() const { return cmd; }
	unsigned int  getDST() const { return dst; }
	unsigned int  getSRC() const { return src; }

private:
	// ** 00 00 �������� �������
	unsigned int cmd;
	// 00 ** 00 �������� ������ ��� ������ ����� ���������( ������ �������� )
	unsigned int dst;
	// 00 00 ** �������� ������ ��� ������ ������ ���������( ������ �������� )
	unsigned int src;
};


class CInterpreter {
public:
	CInterpreter()
	{
		//for( int i = 0; i <= 16; i++ ) {
		//	code.push_back( CRegs() );
		//}
	}
	// ������� � ������� ���
	void printProgramm();
	// ����� ����-��� ��������� � ����
	void writeProgramm( const string& path );
	void writeByteCode( const string& path );
	void readByteCode( const string& path );
	// ������ ��� ��������� �� ����������
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
	void createADDRegs( const vector<string>& tokens );
	void createSUBRegs( const vector<string>& tokens );
	void createCMPRegs( const vector<string>& tokens );
	void createJMPRegs( const vector<string>& tokens );
	void createSHURegs( const vector<string>& tokens );
	void createSHDRegs( const vector<string>& tokens );
	void createOUTCRegs( const vector<string>& tokens );

	//void createJERegs( const vector<string>& tokens );
	//void createJNERegs( const vector<string>& tokens );

	void createSTOPRegs( const vector<string>& tokens );

	void createVARRegs( const vector<string>& tokens );

	void createLABELRegs( const vector<string>& tokens );
	void createRETRegs( const vector<string>& tokens );
	void createCALLRegs( const vector<string>& tokens );
	void restoreLabels();

	void createPUSHRegs( const vector<string>& tokens );
	void createPOPRegs( const vector<string>& tokens );

private:
	unsigned int getVar( const string& name );
	unsigned int getLabelId( const string& name );
	unsigned int getLabelSrc( unsigned int id );

	vector<CRegs> code;
	// ��� ������ ���������� ������ ����� �� ������
	map<string, unsigned int> vars;
	// ��� ������� ������ ������ ��� id
	// ��� ��������� ��������� ���� � call-�� ������� id �������
	// ��� ������ ������� � call ����������� ������ ������ ��� ���������� ������
	map<string, unsigned int> labels;
	map<unsigned int, unsigned int> labelsIdStr;
};