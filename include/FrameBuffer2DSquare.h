#include "FrameBuffer2DRectangle.h"
#pragma once
class FrameBuffer2DSquare : public FrameBuffer2DRectangle{
    // This class represents a memory frame buffer synchronised with a black & white square screen.
    // Each pixel contains a double type representing alpha level/opacity
    // 1.0 will be completely transparent. 0 will be completely opaque.
public:
    FrameBuffer2DSquare(unsigned int dimension);
    unsigned int get_side_length();
};
