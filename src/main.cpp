#include "chip8.h"
#include <iostream>


int main(int argc, char **argv)
{
    if(argc <2)
    {
        std::cout << "Usage c8.exe rom\n";
        return 1;
    }

    Chip8 c8;
    c8.LoadApplication(argv[1]);
}
