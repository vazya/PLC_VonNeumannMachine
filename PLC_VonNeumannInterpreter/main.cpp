#include "Interpreter.h"

int main()
{
	CInterpreter interpreter;
	interpreter.readProgramm( "C:\\Users\\user\\Documents\\Visual Studio 2015\\Projects\\PLC_VonNeumannMachine\\programm.asm" );
	//interpreter.readProgramm( "programm.asm" );
	interpreter.writeProgramm( "C:\\Users\\user\\Documents\\Visual Studio 2015\\Projects\\PLC_VonNeumannMachine\\binarcode" );
}