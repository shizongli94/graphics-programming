#include "FrameBuffer2DRectangle.h"
#include <cmath>
#pragma once

class Drawer2DRectangle{
private:
    FrameBuffer2DRectangle* frame;
    unsigned int width;
    unsigned int height;
public:
    Drawer2DRectangle(FrameBuffer2DRectangle* target_frame);
    ~Drawer2DRectangle();
    void draw_line_segment_dda(double x1, double y1, double x2, double y2, double alpha, bool with_aa);
    void draw_line_segment_bresenham(int x1, int y1, int x2, int y2, double alpha, bool with_aa);
    unsigned int get_width();
    unsigned int get_height();
    void clear_screen();
};