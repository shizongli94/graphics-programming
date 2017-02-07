#pragma once
#include "../include/Command.h"

Command::Command() {
    opcode = 0;
    x = 0;
    y = 0;
}

int Command::get_opcode() {
    return opcode;
}

void Command::set_command(int operation_code, double index_x, double index_y) {
    opcode = operation_code;
    x = index_x;
    y = index_y;
}

double Command::get_x() {
    return x;
}

double Command::get_y() {
    return y;
}