#include "chip8.h"
#include "Instruction.h"
#include <GL/glut.h>
#include <iostream>
#include <bitset>

// Display size
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

int modifier = 10;

// Window size
int display_width = SCREEN_WIDTH * modifier;
int display_height = SCREEN_HEIGHT * modifier;

void display()
{
    glutSwapBuffers();
    glClear(GL_COLOR_BUFFER_BIT);
    
}

void bitwiseTest()
{
    int a = 0xF000;
    int b = 19;
    int c = a & b;
    std::cout << a << " " << b << " " << c << "\n";

    std::bitset<32> ba (a);
    std::bitset<32> bb (b);
    std::bitset<32> bor (a|b);
    std::bitset<32> band (a&b);
    std::bitset<32> bshift (a<<8);
    std::cout << ba << " " << bb << "\n";
    std::cout << bor << " " << band << " " << bshift <<  "\n";
    std::cout << sizeof(unsigned short) << "\n";
}

void instructionTest()
{
    Instruction i(0xF000,
        [](){
            std::cout << "Print MaaaEEE\n";
        });
    i.action();
}

int main(int argc, char **argv)
{
    if(argc <2)
    {
        std::cout << "Usage c8.exe rom\n";
        return 1;
    }

    Chip8 c8;
    c8.LoadApplication(argv[1]);
    for(int i = 0; i < 7; i++)
    {
        c8.EmulateCycle();
    }
//    bitwiseTest();
//    instructionTest();
    std::cout << "QUE" << sizeof(unsigned short) << "\n";

	glutInit(&argc, argv);          
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(display_width, display_height);
    glutInitWindowPosition(320, 320);
	glutCreateWindow("Chip8 Emulator");
	
	glutDisplayFunc(display);
	glutIdleFunc(display);

    glutMainLoop();
}

