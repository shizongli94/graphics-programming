#include "../include/FrameBuffer2DRectangle.h"
#pragma once
FrameBuffer2DRectangle::FrameBuffer2DRectangle(unsigned int n_of_rs, unsigned int n_of_cs){
    num_of_rows = n_of_rs;
    num_of_cols = n_of_cs;
    buffer_size = num_of_cols * num_of_rows;
    buffer = new double[buffer_size];
    clear_buffer();
}
double FrameBuffer2DRectangle::get_alpha_at(int x, int y) {
    return buffer[num_of_cols * y + x];
}
void FrameBuffer2DRectangle::set_alpha_at(int x, int y, double alpha) {
    if (x >= num_of_cols - 1 || y >= num_of_rows - 1) return;
    buffer[num_of_cols * y + x] = alpha;
}

unsigned int FrameBuffer2DRectangle::get_num_of_cols() {
    return num_of_cols;
}

unsigned int FrameBuffer2DRectangle::get_num_of_rows() {
    return num_of_rows;
}

void FrameBuffer2DRectangle::clear_buffer(){
    for (unsigned int i=0; i<buffer_size; i++){
        buffer[i] = 1.0;
    }
}