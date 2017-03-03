#include <iostream>
#include <Magick++.h>
#include "include/Screen2DSquare.h"
#include "include/Drawer2DRectangle.h"
#include "include/Transformer2D.h"
#include "include/DisplayFileInterpreter2DRectangle.h"



using namespace Magick;
int main() {
    std::cout << MaxRGB << std::endl;
    Screen2DSquare* screen;
    Drawer2DRectangle* drawer;
    DisplayFileInterpreter2DRectangle* display_file;
    Transformer2D* transformer;

    Image* first_frame;

    screen = new Screen2DSquare(250);
    transformer = new Transformer2D();
    transformer->stretch(0.5, 0.5);
    transformer->rotate(0.5, true);
    drawer = new Drawer2DRectangle(screen->get_frame_buffer());
    display_file = new DisplayFileInterpreter2DRectangle(drawer, transformer);
    display_file->set_fill(true);
    display_file->set_fill_intensity(0.67);
    double X[5] = {0.2, 0.7, 0.35, 0.4, 0.6};
    double Y[5] = {0.5, 0.5, 0, 0.65, 0};
    display_file->poly_abs_2(X, Y, 5);

    display_file->interpret();
    screen->sync();
    first_frame = screen->get_frame();
    first_frame->magick("png");
    first_frame->write("tt.png");
    return 0;
}