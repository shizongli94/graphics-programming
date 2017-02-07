#include <iostream>
#include <Magick++.h>
#include "include/Screen2DSquare.h"
#include "include/Drawer2DRectangle.h"
#include "include/DisplayFileInterpreter2DRectangle.h"

using namespace Magick;
int main() {
    std::cout << MaxRGB << std::endl;
    Screen2DSquare* screen;
    Drawer2DRectangle* drawer;
    DisplayFileInterpreter2DRectangle* display_file;

    Image* first_frame;

    screen = new Screen2DSquare(250);
    drawer = new Drawer2DRectangle(screen->get_frame_buffer());
    display_file = new DisplayFileInterpreter2DRectangle(drawer);

    display_file->move_abs_2(0.15,0.1);
    display_file->line_abs_2(0.1,0.4);
    display_file->line_abs_2(0.25,0.5);
    display_file->line_abs_2(0.4,0.4);
    display_file->line_abs_2(0.35,0.1);
    display_file->line_abs_2(0.15,0.1);

    display_file->move_rel_2(0.4,0.4);
    display_file->line_rel_2(-0.05,0.3);
    display_file->line_rel_2(0.15,0.1);
    display_file->line_rel_2(0.15,-0.1);
    display_file->line_rel_2(-0.05,-0.3);
    display_file->line_rel_2(-0.2,0);

    display_file->interpret();

    screen->sync();
    first_frame = screen->get_frame();
    first_frame->magick("png");
    first_frame->write("second_frame.png");
    return 0;
}