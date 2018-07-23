//
// Created by Marshal on 29/03/2018.
//

#ifndef UNTITLED_MAIN_H
#define UNTITLED_MAIN_H

#include <vector>

struct point {
    double x;
    double y;
    double z;
};

struct connection {
    int start;
    int end;
};

static std::vector <struct connection> connections;
static std::vector <struct point> points;

#endif //UNTITLED_MAIN_H
