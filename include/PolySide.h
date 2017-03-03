#pragma once

class PolySide{
private:
    int x1, x2, y1, y2;
    bool is_set;
    int winder;
    double current_x;
    double dx;
public:
    PolySide();
    PolySide(PolySide& obj);
    void set(int x1p, int y1p, int x2p, int y2p);
    int get_high_y();
    bool get_is_set();
    int get_high_x();
    int get_low_y();
    int get_low_x();
    int get_winder();
    void set_winder(int direction);
    int get_x1();
    int get_y1();
    int get_x2();
    int get_y2();
    double get_x();
    void incre_x();
};