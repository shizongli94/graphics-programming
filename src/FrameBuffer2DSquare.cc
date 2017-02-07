#include "../include/FrameBuffer2DSquare.h"
#pragma once
FrameBuffer2DSquare::FrameBuffer2DSquare(unsigned int dimension) : FrameBuffer2DRectangle(dimension, dimension){

}

unsigned int FrameBuffer2DSquare::get_side_length() {
    return get_num_of_rows();
}

