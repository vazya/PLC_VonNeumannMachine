#include "VMachine.h"

int main()
{
	CVMachine vMachine;
	//vMachine.readProgramm( "C:\\Users\\user\\Documents\\Visual Studio 2015\\Projects\\PLC_VonNeumannMachine\\binarcode" );
	//vMachine.processProgramm();
	//vMachine.printProgramm();
	vMachine.readByteCode( "C:\\Users\\user\\Documents\\Visual Studio 2015\\Projects\\PLC_VonNeumannMachine\\bytecode" );
	vMachine.processProgramm();
}