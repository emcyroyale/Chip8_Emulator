#include "chip8.h"
#include <fstream>
#include <iostream>
#include <bitset>

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


    //Setup Instructions
    inst[0] = Instruction(0xF000,
        [](){
            std::cout << "Print MEEE\n";
        });
    inst[0].action();
    
}

void Chip8::EmulateCycle()
{
    this->opcode = this->memory[pc] << 8 | this->memory[pc + 1];
    std::bitset<16> op (this->opcode);
    unsigned short ins = 0x22FC;
    std::bitset<16> iop (ins);
    std::cout << std::hex << op << " " << this->opcode << " " << ins << " " << iop <<  "\n";
    std::cout << std::dec << ((int)this->opcode) << " " << ((int)ins) << "\n";

    if(this->opcode==(unsigned short)0x22FC)
    {
        std::cout << "YYOYOYOYOY1111\n";
    }

    if(this->opcode==ins)
    {
        std::cout << "YYOYOYOYOY2222\n";
    }


    pc += 2;
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

//    for(int i = 0; i < (int)file_size; i++){
//        std::cout << buffer[i];
//    }

    //Read into memory
    if(4096-512 > (int)file_size)
    {
        for(int i = 0; i < (int)file_size; i++){
            this->memory[i + 512] = buffer[i];    
        }
    } 
    else
        std::cout << "ROM too big for memory\n";

    ifs.close();
    return true;
}
