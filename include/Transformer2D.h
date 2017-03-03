#pragma once
#include <math.h>

class Transformer2D{
private:
    double * matrix;

    double transformed_x;
    double transformed_y;

    int free;
    int capacity;

    void new_transformation(double* new_transformation);
public:
    Transformer2D();
    ~Transformer2D();
    void stretch_horizontally(double factor);
    void stretch_vertically(double factor);
    void stretch(double x_factor, double y_factor);
    void translate(double dx, double dy);
    void translate_horizontally(double dx);
    void translate_vertically(double dy);
    void rotate(double angle, bool counterclockwise);
    void execute(double x, double y);
    double get_x();
    double get_y();
};