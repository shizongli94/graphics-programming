#include "../include/Transformer2D.h"

#define INIT_CAPACITY 10
#define STRETCH 0
#define ROTATE 1

Transformer2D::Transformer2D() {
    matrix = new double[9];
    // set to identity matrix
    for (int i=0; i<9; i++){
        matrix[i] = 0;
    }
    matrix[0] = 1;
    matrix[4] = 1;
    matrix[8] = 1;
}
Transformer2D::~Transformer2D() {
    delete [] matrix;
}

double Transformer2D::get_x() {
    return transformed_x;
}
double Transformer2D::get_y() {
    return transformed_y;
}

void Transformer2D::new_transformation(double* new_matrix) {
    // implement matrix multiplication between 2 3x3 matrices
    double result[9] = {0};
    double r1, r2, r3, c1, c2, c3;
    for (int i=0; i<9; i+=3){
        r1 = matrix[i];
        r2 = matrix[i+1];
        r3 = matrix[i+2];
        for (int j=0; j<3; j++){
            c1 = new_matrix[j];
            c2 = new_matrix[j+3];
            c3 = new_matrix[j+6];
            result[i+j] = r1*c1 + r2*c2 + r3*c3;
        }
    }
    for (int i=0; i<9; i++){
        matrix[i] = result[i];
    }
}
void Transformer2D::stretch(double x_factor, double y_factor) {
    double stretcher[9] = {0};
    stretcher[0] = x_factor;
    stretcher[4] = y_factor;
    stretcher[8] = 1;
    new_transformation(stretcher);
}
void Transformer2D::stretch_horizontally(double factor) {
    stretch(factor, 1);
}
void Transformer2D::stretch_vertically(double factor) {
    stretch(1, factor);
}

void Transformer2D::rotate(double angle, bool counterclockwise) {
    if (!counterclockwise){
        angle = 0-angle;
    }
    double rotater[9] = {0};
    rotater[0] = cos(angle);
    rotater[1] = sin(angle);
    rotater[3] = 0-sin(angle);
    rotater[4] = cos(angle);
    rotater[8] = 1;
    new_transformation(rotater);
}

void Transformer2D::translate(double dx, double dy) {
    double translater[9] = {0};
    translater[0] = 1;
    translater[4] = 1;
    translater[8] = 1;
    translater[6] = dx;
    translater[7] = dy;
    new_transformation(translater);
}
void Transformer2D::translate_horizontally(double dx) {
    translate(dx, 0);
}
void Transformer2D::translate_vertically(double dy) {
    translate(0, dy);
}
void Transformer2D::execute(double x, double y) {
    double w = 1;
    transformed_x = x*matrix[0] + y*matrix[3] + w*matrix[6];
    transformed_y = x*matrix[1] + y*matrix[4] + w*matrix[7];
}