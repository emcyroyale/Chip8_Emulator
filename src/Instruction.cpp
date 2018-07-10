#include "Instruction.h"

Instruction::Instruction(){}

Instruction::Instruction(unsigned short op, std::function<void ()> func):opcode(op), action_function(func) {}

bool Instruction::action()
{
    this->action_function();
    return true;
}

