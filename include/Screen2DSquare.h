#include "FrameBuffer2DSquare.h"
#include <Magick++.h>
#define DEFAULT_SCREEN_DIMENSION 100
#pragma once

using namespace Magick;
class Screen2DSquare{
    // This class represents a square black & white screen. It reads from a frame buffer to generate one frame
    // , which is represented by an ImageMagick Image object.

private:
    FrameBuffer2DSquare* frame_buffer;
    Image* frame;
public:
    Screen2DSquare(unsigned int dimension);
    Screen2DSquare();
    ~Screen2DSquare();

    void sync();
    Image* get_frame();
    FrameBuffer2DSquare* get_frame_buffer();
};