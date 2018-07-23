#ifndef DRAWER_H
#define DRAWER_H

#include "canvas.h"
#include "connection.h"
#include "point.h"
#include <vector>
#include "data.h"

//class Drawer{
//private:
//    Canvas *canvas;
//public:
//    Drawer(Canvas *cnv){
//        this->canvas = canvas;
//    }
//    ~Drawer(){

//    }

//    void DrawEdge(std::vector<Point> points, std::Connection<connection> connection){
//        int i;
//        drawLine(points[connection[i].get_begin()].get_x(), points[connection[i].get_begin()].get_y(), \
//                 points[connection[i].get_end()].get_x(), points[connection[i].get_end()].get_y());
//    }

//    void DrawEdges(vector points, vector connections){
//        int connections_size = connections.size();

//        for (int i = 0; i < connections_size; i++)
//        {
//            DrawEdge(points, connections[i]);
//        }

//        void DrawModel (Model *mdl){
//            canvas->sceneClear();
//            DrawEdges(mdl.points, mdl.connections);
//        }

//    }

//};

#endif // DRAWER_H
