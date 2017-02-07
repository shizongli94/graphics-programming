#pragma once
#include "Drawer2DRectangle.h"
#include "Command.h"

class DisplayFileInterpreter2DRectangle{
    // to use this class, we need a target drawer to issue the command
    // a way of reading the commands.
private:
    Command* cmds;
    int free, capacity;
    bool erase_flag;
    double pen_x, pen_y, real_pen_x, real_pen_y;
    unsigned int target_width, target_height;
    void expand();
    void domove(double target_x, double target_y);
    void doline(double target_x, double target_y);
    Drawer2DRectangle* drawer;

public:
    DisplayFileInterpreter2DRectangle(Drawer2DRectangle* target_drawer);
    ~DisplayFileInterpreter2DRectangle();
    void start_new_frame();
    void put_cmd(int op, double op_x, double op_y);

    void move_abs_2 (double x, double y);
    void line_abs_2 (double x, double y);
    void move_rel_2 (double dx, double dy);
    void line_rel_2 (double dx, double dy);

    void interpret(); // interpret every command
    void interpret(int start, int bound); // interpret from start through bound-1
};