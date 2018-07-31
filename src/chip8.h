#pragma once
#ifndef CHIP8_H
#define CHIP8_H

#include "Instruction.h"

class Chip8
{
    public:

    bool drawFlag;

    unsigned char display[64 * 32];
    unsigned char key_code[16];

    void EmulateCycle();
    bool LoadApplication(const char * romname); 

    private:
    
    unsigned short pc;
    unsigned short opcode;
    unsigned short i_reg;
    unsigned short sp;

    unsigned char V[16];
    unsigned short stack[16];
    unsigned char memory[4096]; 
    unsigned char  delay_timer;
    unsigned char  sound_timer;

    Instruction inst[36];

    
    void Initialize();

};
#endif
