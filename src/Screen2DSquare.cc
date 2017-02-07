
#include "../include/Screen2DSquare.h"
#pragma once
Screen2DSquare::Screen2DSquare(unsigned int dimension) {
    frame_buffer = new FrameBuffer2DSquare(dimension);
    frame = new Image(Geometry(frame_buffer->get_side_length(), frame_buffer->get_side_length()), Color("white"));
}

Screen2DSquare::Screen2DSquare() {
    frame_buffer = new FrameBuffer2DSquare(DEFAULT_SCREEN_DIMENSION);
    frame = new Image(Geometry(frame_buffer->get_side_length(), frame_buffer->get_side_length()), Color("white"));
}

Screen2DSquare::~Screen2DSquare() {
    delete frame_buffer;
}

void Screen2DSquare::sync() {
    // Returning Image object as if to put graphics on a screen
    unsigned int size = frame_buffer->get_side_length();
    for (unsigned int i=0; i < size; i++){
        for (unsigned int j=0; j < size; j++){
            frame->pixelColor(i, j, ColorGray(frame_buffer->get_alpha_at(i, size - j - 1)));
        }
    }
}

Image* Screen2DSquare::get_frame() {
    return frame;
}

FrameBuffer2DSquare* Screen2DSquare::get_frame_buffer() {
    return frame_buffer;
}