#pragma once

#include "../include/DisplayFileInterpreter2DRectangle.h"

#define INIT_CAPACITY 100
#define OPCODE_DRAW_LINE 2
#define OPCODE_MOVE_PEN 1
#define INIT_FILL_INTENSITY 1

DisplayFileInterpreter2DRectangle::DisplayFileInterpreter2DRectangle(Drawer2DRectangle *target_drawer, Transformer2D* target_transformer) {
    drawer = target_drawer;
    transformer = target_transformer;
    capacity = INIT_CAPACITY;
    free = 0;
    erase_flag = false;
    pen_x = pen_y = 0;
    real_pen_x=real_pen_y=0;
    cmds = new Command [capacity];
    target_width = drawer->get_width();
    target_height = drawer->get_height();
    fill = false;
    fill_intensity = INIT_FILL_INTENSITY;
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
void DisplayFileInterpreter2DRectangle::put_cmd(int op, double op_x, double op_y, double op_a) {
    if (free >= capacity){
        expand();
    }
    cmds[free].set_command(op, op_x, op_y);
    cmds[free].set_alpha(op_a);
    free++;
}

void DisplayFileInterpreter2DRectangle::start_new_frame() {
    erase_flag = true;
}

void DisplayFileInterpreter2DRectangle::set_fill(bool yes_fill) {
    fill = yes_fill;
}

void DisplayFileInterpreter2DRectangle::set_fill_intensity(double intensity) {
    fill_intensity = intensity;
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

void DisplayFileInterpreter2DRectangle::poly_abs_2(double *xx, double *yy, int sides) {
    // move pen to the first vertex
    pen_x = xx[0];
    pen_y = yy[0];
    if (fill){
        put_cmd(sides, pen_x, pen_y, fill_intensity);
    }else{
        put_cmd(sides, pen_x, pen_y);
    }

    double x, y;
    for(int i=1; i < sides; i++){
        x = xx[i];
        y = yy[i];
        line_abs_2(x, y);
    }
    line_abs_2(xx[0], yy[0]); // the last side of polygon
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

void DisplayFileInterpreter2DRectangle::poly_rel_2(double *xx, double *yy, int sides) {
    pen_x += xx[0];
    pen_y += yy[0];
    if (fill){
        put_cmd(sides, pen_x, pen_y, fill_intensity);
    }else{
        put_cmd(sides, pen_x, pen_y);
    }

    double init_x, init_y;
    init_x = pen_x;
    init_y = pen_y;
    double x, y;
    for (int i=1; i < sides;i++){
        x = xx[i];
        y = yy[i];
        line_rel_2(x, y);
    }
    line_abs_2(init_x, init_y);
}

void DisplayFileInterpreter2DRectangle::doline(double target_x, double target_y) {
    double start_x = real_pen_x * target_width;
    double start_y = real_pen_y * target_height;
    real_pen_x = target_x;
    real_pen_y = target_y;
    double end_x = real_pen_x * target_width;
    double end_y = real_pen_y * target_height;
    drawer->draw_line_segment_dda(start_x, start_y, end_x, end_y, 0, true);
}

void DisplayFileInterpreter2DRectangle::domove(double target_x, double target_y) {
    real_pen_x = target_x;
    real_pen_y = target_y;
}

void DisplayFileInterpreter2DRectangle::interpret() {
    interpret(0, free);
}

void DisplayFileInterpreter2DRectangle::sort_by_max_y(PolySide *sides, int len) {
    PolySide temp;
    if (len<=1)
        return;
    for (int k=len;k>0;k--){
        for (int i=0; i<k-1;i++){
            if (sides[i].get_high_y()<sides[i+1].get_high_y()){
                temp = sides[i];
                sides[i] = sides[i+1];
                sides[i+1] = temp;
            }
        }
    }
}
void DisplayFileInterpreter2DRectangle::sort_by_min_y_portion(PolySide *sides, int s, int e) {
    PolySide temp;
    if (e-s<=1)
        return;
    for (int k=e;k>s;k--){
        for (int i=s; i<k-1;i++){
            if (sides[i].get_low_y()<sides[i+1].get_low_y()){
                temp = sides[i];
                sides[i] = sides[i+1];
                sides[i+1] = temp;
            }
        }
    }
}
void DisplayFileInterpreter2DRectangle::sort_by_current_x(PolySide *sides, int s, int e) {
    PolySide temp;
    if (e-s<=1)
        return;
    for (int k=e;k>s;k--){
        for (int i=s; i<k-1;i++){
            if (sides[i].get_x()>sides[i+1].get_x()){
                temp = sides[i];
                sides[i] = sides[i+1];
                sides[i+1] = temp;
            }
        }
    }
}

void DisplayFileInterpreter2DRectangle::dopolygon(int i) {
    Command* cmd;
    PolySide* sides;
    PolySide* side;
    int x1, x2, y1, y2;
    double px, py;
    double x,y;
    int lowest_y = target_height;
    int low_y;
    double intensity;
    bool do_fill;
    cmd = &cmds[i];

    px = cmd->get_x();
    py = cmd->get_y();
    transformer->execute(px, py);
    px = transformer->get_x();
    py = transformer->get_y();

    intensity = cmd->get_alpha();
    do_fill = intensity < 1 && intensity >= 0;
    domove(px, py);

    int sides_ct = cmd->get_opcode();
    int ct = 0;
    sides = new PolySide[sides_ct];

    for (int k=i+1;k<=i+sides_ct;k++){
        cmd = &cmds[k];
        x = cmd->get_x();
        y = cmd->get_y();
        transformer->execute(x, y);
        x = transformer->get_x();
        y = transformer->get_y();
        if (!do_fill){
            doline(x, y);
        }else{
            // add to sides array
            sides[ct].set(int(px*target_width), int(py*target_height),int(x*target_width), int(y*target_height));
            low_y = sides[ct].get_low_y();
            if (low_y < lowest_y){
                lowest_y = low_y;
            }
            ct++;
        }
        px = x;
        py = y;
    }
    // assign winding numbers
    if (do_fill){
        for (int t=0; t<sides_ct; t++){
            side = &sides[t];
            y1 = side->get_y1();
            y2 = side->get_y2();
            x1 = side->get_x1();
            x2 = side->get_x2();
            if ((y2>y1) || (y2==y1 && x2 < x1)){
                side->set_winder(1);
            }else{
                side->set_winder(-1);
            }
        }


        // sort sides by y-max
        sort_by_max_y(sides, sides_ct);
        // draw
        int s=0;
        int e=0;
        int y_max = sides[0].get_high_y();
        if (lowest_y<0)
            lowest_y=0;
        for (int scan=y_max; scan>lowest_y; scan--){
            while(e<sides_ct && sides[e].get_high_y()>=scan)
                e++;

            // sort by min y
            sort_by_min_y_portion(sides, s, e);
            while (sides[s].get_low_y()>scan)
                s++;
            for (int t=s; t<e; t++){
                sides[t].incre_x();
            }
            // sort x
            sort_by_current_x(sides, s, e);
            // draw
            int winders=0;
            double prev_x=0;
            double this_x;
            bool draw_it = false;
            for (int t=s; t<e; t++){
                side = &sides[t];
                this_x = side->get_x();
                winders += side->get_winder();
                if (draw_it){
                    drawer->draw_line_segment_bresenham(int(prev_x), scan, int(this_x), scan, intensity, false);
                }
                if (winders!=0)
                    draw_it=true;
                else
                    draw_it=false;
                prev_x = this_x;
            }
        }
    }
    delete [] sides;
}


void DisplayFileInterpreter2DRectangle::interpret(int start, int bound) {
    Command* cmd;
    int operation;
    double px, py;
    if (erase_flag){
        drawer->clear_screen();
    }

    for (int i=start; i<bound; i++){
        cmd = &cmds[i];
        operation = cmd->get_opcode();
        px = cmd->get_x();
        py = cmd->get_y();
        transformer->execute(px, py);
        px = transformer->get_x();
        py = transformer->get_y();
        if (operation == OPCODE_DRAW_LINE){
            doline(px, py);
        }else if(operation == OPCODE_MOVE_PEN){
            domove(px, py);
        }else if (operation > OPCODE_DRAW_LINE){
            dopolygon(i);
            i = i+operation+1;
        }
    }
}
