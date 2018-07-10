#pragma once
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <functional>

class Instruction
{
    private:
        std::function<void ()> action_function;

    public:
        Instruction();
        Instruction(unsigned short op, std::function<void ()> func);
        unsigned short opcode;
        bool action();
    
};
#endif
