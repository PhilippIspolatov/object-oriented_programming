#ifndef DATA_H
#define DATA_H

#include <vector>
#include "point.h"
#include "connection.h"
#include <math.h>
#include "canvas.h"
#include <iostream>
#include "base_data.h"

class CarcaseModel : public Base_Model {
private:
    //int point_count;
    std::vector <Point> points;
    //sint connection_count;
    std::vector <Connection> connections;
public:
    CarcaseModel() = default;

    CarcaseModel(std::vector<Point> points, std::vector <Connection> connections){
        this->points = points;
        this->connections = connections;
    }

    std::vector<Point> getPoints() {
        return points;
    }
    std::vector<Connection> getCon() {
        return connections;
    }

    void scale(double koef_x, double koef_y, double koef_z){
        int size = points.size();
        for (int i = 0; i < size; i++){
            points[i].set_x(points[i].get_x() * koef_x);
            points[i].set_y(points[i].get_y() * koef_y);
            points[i].set_z(points[i].get_z() * koef_z);
        }
    }

    void shift(double dx, double dy, double dz){
        int size = points.size();
        for (int i = 0; i < size; i++){
            points[i].set_x(points[i].get_x() + dx);
            points[i].set_y(points[i].get_y() + dy);
            points[i].set_z(points[i].get_z() + dz);
        }
    }

    void rotate_x(double angle)
    {
        int size = points.size();
        double tmp_y;
        double tmp_z;

        for (int i = 0; i < size; i++)
        {
            tmp_y = points[i].get_y();
            tmp_z = points[i].get_z();
            points[i].set_x (points[i].get_x());
            points[i].set_y (tmp_y * cos(angle) + tmp_z * sin(angle));
            points[i].set_z ( -tmp_y * sin(angle) + tmp_z * cos(angle));
        }

    }

    void rotate_y(double angle)
    {
        int size = points.size();
        double tmp_x;
        double tmp_z;

        for (int i = 0; i < size; i++)
        {
            tmp_x = points[i].get_x();
            tmp_z = points[i].get_z();
            points[i].set_x ( tmp_x * cos(angle) + tmp_z * sin(angle));
            points[i].set_y ( points[i].get_y());
            points[i].set_z (-tmp_x * sin(angle) + tmp_z * cos(angle));
        }

    }

    void rotate_z(double angle)
    {
        int size = points.size();
        double tmp_x;
        double tmp_y;

        for (int i = 0; i < size; i++)
        {
            tmp_x = points[i].get_x();
            tmp_y = points[i].get_y();

            points[i].set_x ( tmp_x * cos(angle) - tmp_y * sin(angle));
            points[i].set_y ( tmp_x * sin(angle) + tmp_y * cos(angle));
            points[i].set_z ( points[i].get_z());
        }

    }

    void rotate(double ax, double ay, double az){
        rotate_x(ax);
        rotate_y(ay);
        rotate_z(az);
    }

    void draw(Canvas<QGraphicsScene> *ptr){
        ptr->sceneClear();
        int connection_size = connections.size();
        for (int i = 0; i < connection_size; i++)
        {
            ptr->drawLine(points[connections[i].get_begin()].get_x(), points[connections[i].get_begin()].get_y(), \
                    points[connections[i].get_end()].get_x(), points[connections[i].get_end()].get_y());
        }
    }

};

#endif // DATA_H
