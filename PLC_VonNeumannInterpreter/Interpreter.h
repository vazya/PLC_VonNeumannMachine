#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*
���� ������ :
00
01
..
FF
*/

struct regs {
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;
};


class CInterpreter {
public:
	// ������ ��� ��������� �� ����������
	void readProgramm( const string& path );
	// ����� ����-��� ��������� � ����
	void writeProgramm( const string& path );

private:
	vector<regs> code;
};