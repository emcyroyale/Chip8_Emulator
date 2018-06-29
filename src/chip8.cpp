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

    std::ifstream ifs (romname, std::ifstream::binary | std::ifstream::ate );
    std::streampos file_size = ifs.tellg();
    ifs.seekg(0, std::ios_base::beg);

    //Read into buffer
    char buffer[(int)file_size];
    if(ifs.read(buffer, file_size))
    {
        std::cout << "LoadApplication: Load into buffer\n";
    }

    //Read into memory

    ifs.close();
}
