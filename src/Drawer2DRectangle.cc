#include "../include/Drawer2DRectangle.h"
#pragma once

Drawer2DRectangle::Drawer2DRectangle(FrameBuffer2DRectangle *target_frame) {
    frame = target_frame;
    width = frame->get_num_of_cols();
    height = frame->get_num_of_rows();
}

Drawer2DRectangle::~Drawer2DRectangle() {
    delete frame;
}

void Drawer2DRectangle::draw_line_segment_dda(double x1, double y1, double x2, double y2, double alpha, bool with_aa) {
    double dx, dy;
    double m, b;
    int start_index, end_index, select;
    double H;
    double temp;
    double intensity;
    dx = x2 - x1;
    dy = y2 - y1;
    if (fabs(dx) > fabs(dy)){
        m = dy / dx;
        b = y1 - m * x1;
        start_index = int(ceil(fmin(x1, x2)));
        end_index = int(floor(fmax(x1, x2)));
        temp = m*start_index + b;
        select = int(round(temp));
        if (m > 0)
            H = temp - select;
        else
            H = temp - select - 1;
        for (int i=start_index; i<=end_index; i++){
            // if with anti-aliasing, draw neighbor pixel.
            if (with_aa){
                if (m > 0) {
                    intensity = fabs(H - 0.5);
                    if (fabs(H) > 0.5){
                        frame->set_alpha_at(i, select + 1, (1-alpha)*(1-intensity));
                    }else{
                        frame->set_alpha_at(i, select - 1, (1-alpha)*(1-intensity));
                    }
                }else {
                    intensity = fabs(H + 0.5);
                    if (fabs(H) < 0.5){
                        frame->set_alpha_at(i, select + 1, (1-alpha)*(1-intensity));
                    }else{
                        frame->set_alpha_at(i, select - 1, (1-alpha)*(1-intensity));
                    }
                }
            }else
                intensity = alpha;



            frame->set_alpha_at(i, select, intensity);
            H = H + m;
            if (H >= 1){
                select += 1;
                H = H - 1;
            }
            if (H <= -1){
                select -= 1;
                H = H + 1;
            }
        }
    }else{
        m = dx / dy;
        b = x1 - m * y1;
        start_index = int(ceil(fmin(y1, y2)));
        end_index = int(floor(fmax(y1, y2)));
        temp = m*start_index + b;
        select = int(round(temp));
        if (m > 0){
            H = temp -select;
        }else{
            H = temp - select -1;
        }
        for (int i=start_index; i<=end_index; i++){
            if (with_aa){
                if (m > 0) {
                    intensity = fabs(H - 0.5);
                    if (fabs(H) > 0.5){
                        frame->set_alpha_at( select + 1, i, 1-intensity);
                    }else{
                        frame->set_alpha_at( select - 1, i, 1-intensity);
                    }
                }else {
                    intensity = fabs(H + 0.5);
                    if (fabs(H) < 0.5){
                        frame->set_alpha_at( select + 1, i, 1-intensity);
                    }else{
                        frame->set_alpha_at( select - 1, i, 1-intensity);
                    }
                }
            }else
                intensity = 0;

            frame->set_alpha_at(select, i, intensity);
            H = H + m;
            if (H >= 1){
                select += 1;
                H = H - 1;
            }
            if (H <= -1){
                select -= 1;
                H = H + 1;
            }
        }
    }
}

void Drawer2DRectangle::draw_line_segment_bresenham(int x1, int y1, int x2, int y2, double alpha, bool with_aa) {
    int dy, dx;
    int start_index, select, end_index;
    int P;
    dy = y2 - y1;
    dx = x2 - x1;

    if (fabs(dy) < fabs(dx)){
        if (x1 < x2){
            start_index = x1;
            end_index = x2;
            select = y1;
            dx = x2 - x1;
            dy = y2 - y1;
        }else{
            start_index = x2;
            end_index = x1;
            select = y2;
            dx = x1 - x2;
            dy = y1 - y2;
        }

        if (dy > 0){
            P = 2*dy - dx;
            for (int i=start_index; i <=end_index; i++) {
                frame->set_alpha_at(i, select, alpha);
                if (P > 0){
                    select += 1;
                    P = P + 2*dy - 2 * dx;
                }else{
                    P = P + 2*dy;
                }
            }
        }else{
            P = 2 * dy + dx;
            for (int i=start_index; i<=end_index; i++){
                frame->set_alpha_at(i, select, alpha);
                if (P < 0){
                    select -= 1;
                    P = P + 2*dy + 2*dx;
                }else{
                    P = P + 2*dy;
                }
            }
        }

    }else{
        if (y1 < y2){
            start_index = y1;
            end_index = y2;
            select = x1;
            dx = x2 - x1;
            dy = y2 - y1;
        }else{
            start_index = y2;
            end_index = y1;
            select = x2;
            dx = x1 - x2;
            dy = y1 - y2;
        }
        if (dx > 0){
            P = 2*dx - dy;
            for (int i=start_index; i<=end_index; i++){
                frame->set_alpha_at(select, i, alpha);
                if (P > 0){
                    select += 1;
                    P = P + 2*dx - 2*dy;
                }else{
                    P = P + 2*dx;
                }
            }
        }else{
            P = 2*dx + dy;
            for (int i=start_index; i<=end_index; i++){
                frame->set_alpha_at(select, i, alpha);
                if (P < 0){
                    select -= 1;
                    P = P + 2*dx + 2*dy;
                }else{
                    P = P + 2*dx;
                }
            }
        }
    }

}

unsigned int Drawer2DRectangle::get_height() {
    return height;
}
unsigned int Drawer2DRectangle::get_width() {
    return width;
}

void Drawer2DRectangle::clear_screen() {
    frame->clear_buffer();
}