#pragma once

#include "../include/PolySide.h"

PolySide::PolySide() {
    is_set=false;
}
void PolySide::set(int x1p, int y1p, int x2p, int y2p) {
    x1 = x1p;
    y1 = y1p;
    x2 = x2p;
    y2 = y2p;
    if (y2 == y1){
        dx = 0;
    }else{
        dx = double(x1-x2) / double(y1-y2);
    }
    current_x = get_high_x() + dx;
    is_set=true;
}
bool PolySide::get_is_set() {
    return is_set;
}
int PolySide::get_high_x() {
    if (y1 > y2){
        return x1;
    }else{
        return x2;
    }
}
int PolySide::get_high_y() {
    if (y1 > y2){
        return y1;
    }else{
        return y2;
    }
}
int PolySide::get_low_x() {
    if (y1 < y2){
        return x1;
    }else{
        return x2;
    }
}

int PolySide::get_low_y() {
    if (y1 < y2){
        return y1;
    }else{
        return y2;
    }
}
int PolySide::get_winder() {
    return winder;
}
void PolySide::set_winder(int direction) {
    winder = direction;
}

int PolySide::get_x1() {
    return x1;
}
int PolySide::get_y1() {
    return y1;
}
int PolySide::get_x2() {
    return x2;
}
int PolySide::get_y2() {
    return y2;
}
double PolySide::get_x() {
    return current_x;
}
void PolySide::incre_x() {
    current_x = current_x - dx;
}
PolySide::PolySide(PolySide &obj) {
    x1 = obj.x1;
    x2 = obj.x2;
    y1 = obj.y1;
    y2 = obj.y2;
    is_set = obj.is_set;
    winder = obj.winder;
    current_x = obj.current_x;
    dx = obj.dx;
}