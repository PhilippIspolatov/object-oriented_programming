#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <vector>
#include "data.h"
#include "exception.h"
#include <iostream>


class File {
protected:
    //char *filename;
    FILE *f;

    Point loadPoint(FILE *f){
        double x, y, z;
        if (fscanf(f, "%lf %lf %lf", &x , &y, &z) != 3)
            throw errorFile();

        Point p(x, y, z);

        return p;
    }

    Connection loadConnection(FILE *f){
        int b, e;
        if (fscanf(f, "%d %d", &b , &e) != 2)
            throw errorFile();

        Connection con(b, e);

        return con;
    }
public:
    File() = default;
    File(char * filename){
        f = fopen(filename, "r");
    }

    ~File() {
        fclose(f);
    }

    void parse(Model &mdl){

        int pointsCount = 0;
        int connectionsCount = 0;

        if (fscanf(f, "%d %d", &pointsCount, &connectionsCount) != 2) {
            return;
        }

        std::vector <Point> points;
        std::vector <Connection> connections;

        for (int i = 0; i < pointsCount; i++){
            points.push_back(loadPoint(f));
        }

        for (int i = 0; i < connectionsCount; i++){
            connections.push_back(loadConnection(f));
        }

        mdl = Model(points, connections);

    }

};

#endif // FILE_H
