#pragma once
#ifndef CHIP8_H
#define CHIP8_H

class Chip8
{
    private:
    
    unsigned char memory[4096]; 
    

    public:

    void EmulateCycle();
    bool LoadApplication(const char * romname); 

};
#endif
