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
    inst[0] = Instruction(0x0000,
        [](){
            std::cout << "Print MEEE\n";
        });
    inst[0].action();
    
}

void Chip8::EmulateCycle()
{
    this->opcode = this->memory[pc] << 8 | this->memory[pc + 1];
    std::bitset<16> op (this->opcode);

    unsigned short proc_op = this->opcode & 0xF000;
    std::bitset<16> pop (proc_op);
    

    std::cout << std::hex << op << " " << this->opcode << " " << "\n";
    std::cout << "Process: " << std::hex << pop << " " << proc_op << "\n";
    std::cout << "________________\n";

    if(this->opcode==(unsigned short)0x22FC)
    {
        std::cout << "YYOYOYOYOY1111\n";
    }

    //Process opcode
    //Figure out which Instruction
    //Run instruction action

    switch(this->opcode & 0xF000)
    {

        case 0x0000:
            //3
            switch(this->opcode & 0x000F)
            {
                case 0x0000: 
                    //Clear Screen - 0x00E0
                    for(unsigned char pixel : gfx)
                    {
                        pixel = 0x0;
                    }
                    this->drawFlag = true; 
                    this->pc += 2;
                break;
                case 0x000E:
                    //Return From Subroutine - 0x00EE
                    --this->sp;
                    this->pc = this->stack[this->sp]
                    this->pc += 2;
                break;
            }
        break;
        case 0x1000:
            //1
            //Jump to Location - 0x1nnn
            unsigned short nnn_mask = this->opcode & 0x0FFF;
            this->pc = nnn_mask;
        break;
        case 0x2000:
            //1
            //Call subroutine - 0x2nnn
            this->stack[this->sp]=pc;
            this->sp++;
            unsigned short nnn_mask = this->opcode & 0x0FFF;
            this->pc = nnn_mask;
        break;
        case 0x3000:
            //1
            //Skip next instruction if Vx == kk - 0x3xkk
            unsigned short x_mask = this->opcode & 0x0F00;
            unsigned short kk_mask = this->opcode & 0x00FF;
            if(this->V[x_mask] == kk_mask)
                this->pc+=4;
            else
                this->pc+=2;
        break;
        case 0x4000:
            //1
            //Skip next instruction if Vx != kk - 0x4xkk
            unsigned short x_mask = this->opcode & 0x0F00;
            unsigned short kk_mask = this->opcode & 0x00FF;
            if(this->V[x_mask] != kk_mask)
                this->pc+=4;
            else
                this->pc+=2;
        break;
        case 0x5000:
            //1
            //Skip next instruction if Vx == Vy - 0x5xy0
            unsigned short x_mask = this->opcode & 0x0F00;
            unsigned short y_mask = this->opcode & 0x00F0;
            if(this->V[x_mask] == this->V[y_mask])
                this->pc+=4;
            else
                this->pc+=2;
        break;
        case 0x6000:
            //1
            //Loads Vx = kk - 0x6xkk
            unsigned short x_mask = this->opcode & 0x0F00;
            unsigned short kk_mask = this->opcode & 0x00FF;
            this->V[x_mask] = kk_mask;
        break;
        case 0x7000:
            //1
            //Adds Vx = Vx + kk - 0x7xkk
            unsigned short x_mask = this->opcode & 0x0F00;
            unsigned short kk_mask = this->opcode & 0x00FF;
            this->V[x_mask] += kk_mask;
        break;
        case 0x8000:
            //9
            switch(this->opcode & 0x000F)
            {
                case 0x0000:
                    //Stores Vx = Vy - 0x8xy0
                    unsigned short x_mask = this->opcode & 0x0F00;
                    unsigned short y_mask = this->opcode & 0x00F0;
                    this->V[x_mask] = this->V[y_mask]
                break;
                case 0x0001:
                    //Sets bitwise Vx = Vx OR Vy - 0x8xy1
                    unsigned short x_mask = this->opcode & 0x0F00;
                    unsigned short y_mask = this->opcode & 0x00F0;
                    this->V[x_mask] |= this->V[y_mask]
                break;
                case 0x0002:
                    //Sets bitwise Vx = Vx AND Vy - 0x8xy2
                    unsigned short x_mask = this->opcode & 0x0F00;
                    unsigned short y_mask = this->opcode & 0x00F0;
                    this->V[x_mask] &= this->V[y_mask]
                break;
                case 0x0003:
                    //Sets bitwise Vx = Vx XOR Vy - 0x8xy3
                    unsigned short x_mask = this->opcode & 0x0F00;
                    unsigned short y_mask = this->opcode & 0x00F0;
                    this->V[x_mask] ^= this->V[y_mask]
                break;
                case 0x0004:
                    //Adds Vx = Vx + Vy and VF=carry - 0x8xy4
                    unsigned short x_mask = this->opcode & 0x0F00;
                    unsigned short y_mask = this->opcode & 0x00F0;
                    this->V[x_mask] += this->V[y_mask]
                break;
                case 0x0005:
                    //Subtracts Vx = Vx - Vy and VF=not borrow- 0x8xy5
                break;
                case 0x0006:
                    //Sets Vx = Vx SHR 1 (Shift Right) - 0x8xy6
                    //If the least significant bit of Vx is 1 then VF=1 otherwise VF=0. Then Vx = Vx/2
                break;
                case 0x0007:
                    //Subtracts Vx = Vy - Vx and VF=not borrow- 0x8xy7
                break;
                case 0x000E:
                    //Sets Vx = Vx SHL 1 (Shift Left) - 0x8xyE
                    //If the least significant bit of Vx is 1 then VF=1 otherwise VF=0. Then Vx = Vx*2
                break;
            }
        break;
        case 0x9000:
            //1
            //Skip next instruction if Vx != Vy - 0x9xy0
        break;
        case 0xA000:
            //1
            //Loads register I = nnn - 0xAnnn
        break;
        case 0xB000:
            //1
            //Jump to location nnn + V0 - 0xBnnn
        break;
        case 0xC000:
            //1
            //Sets Vx = RANDOM(0, 255) AND kk - 0xCxkk
        break;
        case 0xD000:
            //1
            //Draw sprite n starting from (Vx, Vy) - 0xDxyn
        break;
        case 0xE000:
            //2
            switch(this->opcode & 0x00FF)
            {
                case 0x009E:
                    //Skips next instruction if key with value Vx is pressed
                break;
                case 0x00A1:
                    //Skips next instruction if key with value Vx is not pressed
                break;
            }
        break;
        case 0xF000:
            //9
            switch(this->opcode & 0x00FF)
            {
                case 0x0007:
                    //Load Vx=DT delay time - 0xFx07
                break;
                case 0x000A:
                    //Load next Keypress(all execution is halted until press) into Vx - 0xFx0A
                break;
                case 0x0015:
                    //Load DT=Vx delay time - 0xFx15
                break;
                case 0x0018:
                    //Load sound timer ST=Vx - 0xFx18
                break;
                case 0x001E:
                    //Add I = I + Vx - 0xFx1E
                break;
                case 0x0029:
                    //Load I = location of sprite for digit Vx - 0xFx29
                break;
                case 0x0033:
                    //Loads BCD representation in I, I+1, I+2 (hundreds in I, tens in I+1, ones in I+2)
                break;
                case 0x0055:
                    //Loads V0 to Vx into registers starting at I - 0xFx55
                break;
                case 0x0065:
                    //Reads V0 to Vx into registers starting at I - 0xFx65
                break;
            }
        break;

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
