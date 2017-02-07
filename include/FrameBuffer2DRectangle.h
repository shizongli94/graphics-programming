#pragma once
class FrameBuffer2DRectangle{
protected:
    unsigned int num_of_rows;
    unsigned int num_of_cols;
    double* buffer;
    unsigned int buffer_size;
public:
    FrameBuffer2DRectangle(unsigned int n_of_rs, unsigned int n_of_cs);
    double get_alpha_at(int x, int y);
    void set_alpha_at(int x, int y, double alpha);
    unsigned int get_num_of_rows();
    unsigned int get_num_of_cols();
    void clear_buffer();
};