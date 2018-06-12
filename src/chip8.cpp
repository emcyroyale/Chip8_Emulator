#include "chip8.h"
#include <fstream>
#include <iostream>


void Chip8::EmulateCycle()
{

}

bool Chip8::LoadApplication(const char * romname)
{
    std::ifstream ifs (romname, std::ifstream::in);
    
    while(ifs.good())
    {
        std::cout << ifs.get();
    }

    //Read into buffer
    //Read into memory

    ifs.close();
}
