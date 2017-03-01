#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*
коды команд :
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
	// читает код программы на ассембелре
	void readProgramm( const string& path );
	// пишет байт-код программы в файл
	void writeProgramm( const string& path );

private:
	vector<regs> code;
};