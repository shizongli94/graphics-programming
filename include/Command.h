#pragma once

class Command{
private:
    int opcode;
    double x, y;
    double alpha;
public:
    Command();
    int get_opcode();
    void set_command(int operation_code, double index_x, double index_y);
    double get_x();
    double get_y();
    void set_alpha(double a);
    double get_alpha();
};