#pragma once

#include "../include/DisplayFileInterpreter2DRectangle.h"

#define INIT_CAPACITY 100
#define OPCODE_DRAW_LINE 2
#define OPCODE_MOVE_PEN 1

DisplayFileInterpreter2DRectangle::DisplayFileInterpreter2DRectangle(Drawer2DRectangle *target_drawer) {
    drawer = target_drawer;
    capacity = INIT_CAPACITY;
    free = 0;
    erase_flag = false;
    pen_x = pen_y = 0;
    real_pen_x=real_pen_y=0;
    cmds = new Command [capacity];
    target_width = drawer->get_width();
    target_height = drawer->get_height();
}

DisplayFileInterpreter2DRectangle::~DisplayFileInterpreter2DRectangle() {
    delete [] cmds;
}

void DisplayFileInterpreter2DRectangle::expand() {
    Command* new_array_cmds = new Command[2*capacity];
    for (int i=0; i<capacity; i++){
        new_array_cmds[i] = cmds[i];
    }
    delete [] cmds;
    cmds = new_array_cmds;
    capacity *= 2;
}

void DisplayFileInterpreter2DRectangle::put_cmd(int op, double op_x, double op_y) {
    if (free >= capacity){
        expand();
    }
    cmds[free].set_command(op, op_x, op_y);
    free++;
}

void DisplayFileInterpreter2DRectangle::start_new_frame() {
    erase_flag = true;
}

void DisplayFileInterpreter2DRectangle::line_abs_2(double x, double y) {
    pen_x = x;
    pen_y = y;
    put_cmd(OPCODE_DRAW_LINE, pen_x, pen_y);
}

void DisplayFileInterpreter2DRectangle::move_abs_2(double x, double y) {
    pen_x = x;
    pen_y = y;
    put_cmd(OPCODE_MOVE_PEN, pen_x, pen_y);
}

void DisplayFileInterpreter2DRectangle::line_rel_2(double dx, double dy) {
    pen_x += dx;
    pen_y += dy;
    put_cmd(OPCODE_DRAW_LINE, pen_x, pen_y);
}

void DisplayFileInterpreter2DRectangle::move_rel_2(double dx, double dy) {
    pen_x += dx;
    pen_y += dy;
    put_cmd(OPCODE_MOVE_PEN, pen_x, pen_y);
}

void DisplayFileInterpreter2DRectangle::doline(double target_x, double target_y) {
    double start_x = real_pen_x * target_width;
    double start_y = real_pen_y * target_height;
    real_pen_x = target_x;
    real_pen_y = target_y;
    double end_x = real_pen_x * target_width;
    double end_y = real_pen_y * target_height;
    drawer->draw_line_segment_dda(start_x, start_y, end_x, end_y, true);
}

void DisplayFileInterpreter2DRectangle::domove(double target_x, double target_y) {
    real_pen_x = target_x;
    real_pen_y = target_y;
}

void DisplayFileInterpreter2DRectangle::interpret() {
    interpret(0, free);
}

void DisplayFileInterpreter2DRectangle::interpret(int start, int bound) {
    Command* cmd;
    int operation;
    if (erase_flag){
        drawer->clear_screen();
    }

    for (int i=start; i<bound; i++){
        cmd = &cmds[i];
        operation = cmd->get_opcode();
        if (operation == OPCODE_DRAW_LINE){
            doline(cmd->get_x(), cmd->get_y());
        }else if(operation == OPCODE_MOVE_PEN){
            domove(cmd->get_x(), cmd->get_y());
        }
    }
}