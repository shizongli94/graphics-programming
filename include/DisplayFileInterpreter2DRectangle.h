#pragma once
#include "Drawer2DRectangle.h"
#include "Command.h"
#include "PolySide.h"
#include "Transformer2D.h"

class DisplayFileInterpreter2DRectangle{
    // to use this class, we need a target drawer to issue the command
    // a way of reading the commands.
private:
    int capacity;
    Command* cmds;
    int free;
    bool erase_flag, fill;
    double pen_x, pen_y, real_pen_x, real_pen_y;
    double fill_intensity;
    unsigned int target_width, target_height;
    void expand();
    void domove(double target_x, double target_y);
    void doline(double target_x, double target_y);
    void dopolygon(int i);
    void sort_by_max_y(PolySide* sides, int len);
    void sort_by_min_y_portion(PolySide* sides, int s, int e);
    void sort_by_current_x(PolySide* sides, int s, int e);
    Drawer2DRectangle* drawer;
    Transformer2D* transformer;
public:
    DisplayFileInterpreter2DRectangle(Drawer2DRectangle* target_drawer, Transformer2D* target_transformer);
    ~DisplayFileInterpreter2DRectangle();
    void start_new_frame();
    void put_cmd(int op, double op_x, double op_y);
    void put_cmd(int op, double op_x, double op_y, double op_a);
    void move_abs_2 (double x, double y);
    void line_abs_2 (double x, double y);
    void poly_abs_2 (double* xx, double* yy, int sides);
    void move_rel_2 (double dx, double dy);
    void line_rel_2 (double dx, double dy);
    void poly_rel_2 (double* xx, double* yy, int sides);

    void set_fill_intensity(double intensity);
    void set_fill(bool yes_fill);

    void interpret(); // interpret every command
    void interpret(int start, int bound); // interpret from start through bound-1
};