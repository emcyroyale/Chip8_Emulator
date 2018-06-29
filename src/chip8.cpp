#include "chip8.h"
#include <fstream>
#include <iostream>

void Chip8::Initialize()
{
    pc = 0x200;    //Start Address
    opcode = 0;
    i_reg = 0;
    sp = 0;

	for(int i = 0; i < 2048; ++i)
		display[i] = 0;

	// Clear stack
	for(int i = 0; i < 16; ++i)
		stack[i] = 0;

	for(int i = 0; i < 16; ++i)
		key_code[i] = V[i] = 0;

	// Clear memory
	for(int i = 0; i < 4096; ++i)
		memory[i] = 0;
					
    //Clear screen
    drawFlag = true;
}

void Chip8::EmulateCycle()
{

}

bool Chip8::LoadApplication(const char * romname)
{
    Initialize();

    std::ifstream ifs (romname, std::ifstream::in);
    
    while(ifs.good())
    {
        std::cout << ifs.get();
    }

    if (ifs.is_open())
    {
        std::cout << "Yo!\n";

    }
    //Read into buffer
    //Read into memory

    ifs.close();
}
